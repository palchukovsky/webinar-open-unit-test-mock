#include "librarian.hpp"

#include "book.hpp"
#include "database.hpp"
#include "reader.hpp"

namespace Lib {

Librarian::Librarian(std::unique_ptr<Database> db)
    : m_database{std::move(db)} {}

auto Librarian::recognize(std::string_view readerName)
    -> std::pair<Reader, bool> {
  if (auto result = m_database->findReader(std::string{readerName}); result) {
    return {std::move(*result), true};
  }
  return {m_database->insertReader(readerName), false};
}

auto Librarian::getAllBooks() const -> std::vector<Book> {
  return m_database->getAllBooks();
}

auto Librarian::borrowBook(std::string_view isbn, Reader &reader)
    -> std::pair<bool, bool> {
  const auto book = m_database->findBookByIsdn(isbn);
  if (!book) {
    return {false, false};
  }

  const auto borrowed = m_database->borrowBook(*book, reader);
  return {true, borrowed};
}
auto Librarian::returnBook(std::string_view isbn, Reader &reader) -> bool {
  const auto book = m_database->findBookByIsdn(isbn);
  if (!book) {
    return false;
  }

  m_database->returnBook(*book, reader);
  return true;
}

}  // namespace Lib