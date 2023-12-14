#include "pqdatabase.hpp"

#include "book.hpp"
#include "reader.hpp"

#include <cassert>
#include <pqxx/pqxx>

namespace Lib {

class PqDatabase::Impl {
 public:
  [[nodiscard]] auto connection() const -> decltype(auto) {
    return (m_connection);
  }

  [[nodiscard]] auto startWork() const -> pqxx::work {
    return pqxx::work{connection()};
  }

  template <typename... Args>
  [[nodiscard]] auto findBook(const pqxx::zview statement, Args &&...args) const
      -> std::optional<Book> {
    auto work = startWork();

    const auto selection =
        work.exec_prepared(statement, std::forward<Args>(args)...);

    if (selection.empty()) {
      return std::nullopt;
    }
    assert(selection.size() == 1);

    const auto &row = selection[0];
    assert(row.size() == 2);
    return Book{row[0].template as<std::string>(),
                row[1].template as<std::string>()};
  }

 private:
  mutable pqxx::connection m_connection{
      "user=palchukovsky password=mysecretpassword hostaddr=127.0.0.1 "
      "dbname=palchukovsky port=5432"};
};

PqDatabase::PqDatabase() : m_pimpl{new Impl} {
  auto &c = m_pimpl->connection();

  c.prepare("insert_book", "INSERT INTO book (id, title) VALUES ($1, $2)");
  c.prepare("update_book", "UPDATE book SET title = $2 WHERE id = $1");
  c.prepare("delete_book", "DELETE from book WHERE id = $1");

  c.prepare("find_book_by_isbn", "SELECT id, title FROM book WHERE id = $1");
  c.prepare("find_book_by_title",
            "SELECT id, title FROM book WHERE title = $1");

  c.prepare("find_all_books", "SELECT id, title FROM book");

  c.prepare(
      "count_borrows",
      "SELECT COUNT(*) FROM borrow WHERE book = $1 AND return_date IS NULL");

  c.prepare("count_reader_borrows",
            "SELECT book.title FROM borrow"
            " JOIN book ON borrow.book = book.id"
            " JOIN reader ON borrow.reader = reader.id"
            " WHERE reader.id = $1 AND borrow.return_date IS NULL");

  c.prepare("borrow",
            "INSERT INTO borrow (book, reader, borrow_date)"
            " VALUES ($1, $2, CURRENT_TIMESTAMP)");
  c.prepare("return",
            "UPDATE borrow SET return_date = CURRENT_TIMESTAMP"
            " WHERE book = $1 AND reader = $2 AND return_date IS NULL");

  c.prepare("insert_reader",
            "INSERT INTO reader (name) VALUES ($1) RETURNING id");
  c.prepare("find_reader",
            "SELECT reader.id, reader.name FROM reader WHERE reader.name = $1");
}

PqDatabase::~PqDatabase() = default;

void PqDatabase::insertBook(const Book &book) {
  auto work = m_pimpl->startWork();
  work.exec_prepared("insert_book", book.isbn(), book.title());
  work.commit();
}

void PqDatabase::updateBook(const Book &book) {
  auto work = m_pimpl->startWork();
  work.exec_prepared("update_book", book.isbn(), book.title());
  work.commit();
}

void PqDatabase::deleteBook(const Book &book) {
  auto work = m_pimpl->startWork();
  work.exec_prepared("delete_book", book.isbn());
  work.commit();
}

auto PqDatabase::findBookByTitle(const std::string_view title) const
    -> std::optional<Book> {
  return m_pimpl->findBook("find_book_by_isbn", title);
}

auto PqDatabase::findBookByIsdn(const std::string_view isdn) const
    -> std::optional<Book> {
  return m_pimpl->findBook("find_book_by_title", isdn);
}

auto PqDatabase::findBorrowed(const Reader &reader) const -> std::vector<Book> {
  std::vector<Book> result;

  auto work = m_pimpl->startWork();
  const auto selection =
      work.exec_prepared("count_reader_borrows", reader.id());

  result.reserve(selection.size());
  for (const auto &row : selection) {
    assert(row.size() == 2);
    result.emplace_back(row[0].template as<std::string>(),
                        row[1].template as<std::string>());
  }

  return result;
}

auto PqDatabase::insertReader(std::string_view name) -> Reader {
  auto work = m_pimpl->startWork();

  const auto result = work.exec_prepared("insert_reader", name);
  assert(result.size() == 1);
  assert(result[0].size() == 1);
  return Reader{result[0][0].as<int>(), std::string{name}};
}

auto PqDatabase::findReader(std::string name) const
    -> std::optional<Reader> {
  auto work = m_pimpl->startWork();

  const auto selection = work.exec_prepared("find_reader", name);

  if (selection.empty()) {
    return std::nullopt;
  }
  assert(selection.size() == 1);

  const auto &row = selection[0];
  assert(row.size() == 2);
  return Reader{row[0].template as<int>(), row[1].template as<std::string>()};
}

auto PqDatabase::borrowBook(const Book &book, const Reader &reader) -> bool {
  try {
    auto work = m_pimpl->startWork();
    {
      const auto borrowed = work.exec_prepared("count_borrows", book.isbn());
      assert(borrowed.size() == 1);
      assert(borrowed[0].size() == 1);
      if (borrowed[0][0].as<int>() > 0) {
        return false;  // is already borrowed
      }
    }

    work.exec_prepared("borrow", book.isbn(), reader.id());

    work.commit();

  } catch (const std::exception &) {
    return false;
  }

  return true;
}

void PqDatabase::returnBook(const Book &book, const Reader &reader) {
  auto work = m_pimpl->startWork();
  work.exec_prepared("return", book.isbn(), reader.id());
  work.commit();
}

auto PqDatabase::getAllBooks() const -> std::vector<Book> {
  std::vector<Book> result;

  const auto selection = m_pimpl->startWork().exec_prepared("find_all_books");

  result.reserve(selection.size());
  for (const auto &row : selection) {
    assert(row.size() == 2);
    result.emplace_back(row[0].template as<std::string>(),
                        row[1].template as<std::string>());
  }

  return result;
}
}  // namespace Lib
