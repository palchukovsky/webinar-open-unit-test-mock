#pragma once

#include <string>

namespace Lib {

class Book {
 public:
  Book(std::string isbn, std::string title)
      : m_title{std::move(title)}, m_isbn{std::move(isbn)} {}

  bool operator==(const Book &other) const {
    return m_title == other.m_title && m_isbn == other.m_isbn;
  }

  [[nodiscard]] auto title() const -> decltype(auto) { return (m_title); }
  [[nodiscard]] auto isbn() const -> decltype(auto) { return (m_isbn); }

 private:
  std::string m_title;
  std::string m_isbn;
};

}  // namespace Lib