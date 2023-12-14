#pragma once

#include "fwd.hpp"

#include <optional>
#include <string_view>
#include <vector>

namespace Lib {

class Database {
 public:
  Database() = default;
  Database(Database &&) = default;
  Database(const Database &) = delete;
  virtual ~Database() = default;

  auto operator=(Database &&) -> Database & = default;
  auto operator=(Database &) = delete;

  virtual void insertBook(const Book &) = 0;
  virtual void updateBook(const Book &) = 0;
  virtual void deleteBook(const Book &) = 0;

  virtual auto insertReader(std::string_view name) -> Reader = 0;
  [[nodiscard]] virtual auto findReader(std::string name) const
      -> std::optional<Reader> = 0;

  [[nodiscard]] virtual auto getAllBooks() const -> std::vector<Book> = 0;

  [[nodiscard]] virtual auto findBookByTitle(std::string_view title) const
      -> std::optional<Book> = 0;
  [[nodiscard]] virtual auto findBookByIsdn(std::string_view isdn) const
      -> std::optional<Book> = 0;

  [[nodiscard]] virtual auto findBorrowed(const Reader &) const
      -> std::vector<Book> = 0;

  virtual auto borrowBook(const Book &, const Reader &) -> bool = 0;
  virtual void returnBook(const Book &, const Reader &) = 0;
};

}  // namespace Lib