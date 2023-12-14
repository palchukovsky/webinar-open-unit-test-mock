#pragma once

#include "database.hpp"

#include <memory>

namespace Lib {

class PqDatabase : public Database {
 public:
  PqDatabase();
  PqDatabase(PqDatabase &&) = default;
  PqDatabase(const PqDatabase &) = delete;
  ~PqDatabase();

  auto operator=(PqDatabase &&) -> PqDatabase & = default;
  auto operator=(PqDatabase &) = delete;

  void insertBook(const Book &book) override;
  void updateBook(const Book &book) override;
  void deleteBook(const Book &book) override;

  auto insertReader(std::string_view name) -> Reader override;
  auto findReader(std::string name) const
      -> std::optional<Reader> override;

  [[nodiscard]] auto getAllBooks() const -> std::vector<Book> override;

  [[nodiscard]] auto findBookByTitle(std::string_view title) const
      -> std::optional<Book> override;
  [[nodiscard]] auto findBookByIsdn(std::string_view isdn) const
      -> std::optional<Book> override;

  [[nodiscard]] auto findBorrowed(const Reader &) const
      -> std::vector<Book> override;

  auto borrowBook(const Book &book, const Reader &reader) -> bool override;
  void returnBook(const Book &book, const Reader &reader) override;

 private:
  class Impl;
  std::unique_ptr<Impl> m_pimpl;
};

}  // namespace Lib