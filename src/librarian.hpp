#pragma once

#include "reader.hpp"

#include "fwd.hpp"

#include <memory>
#include <string_view>

namespace Lib {

class Librarian {
 public:
  explicit Librarian(std::unique_ptr<Database>);

  Librarian(Librarian &&) = default;
  Librarian(const Librarian &) = delete;
  virtual ~Librarian() = default;

  auto operator=(Librarian &&) -> Librarian & = default;
  auto operator=(Librarian &) = delete;

  virtual auto recognize(std::string readerName) -> std::pair<Reader, bool>;

  auto getAllBooks() const -> std::vector<Book>;

  auto borrowBook(std::string_view isbn, Reader &reader)
      -> std::pair<bool, bool>;
  auto returnBook(std::string_view isbn, Reader &reader) -> bool;

 private:
  std::unique_ptr<Database> m_database;
};

}  // namespace Lib
