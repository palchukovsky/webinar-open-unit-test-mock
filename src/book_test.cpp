#include "book.hpp"

#include <gtest/gtest.h>

#include <string>

using namespace std::literals;
using namespace Lib;

using namespace Lib;

TEST(Book, Create) {
  const auto isbn = "978-3-16-148410-0"s;
  const auto title = "Death Note"s;

  const Lib::Book book{isbn, title};

  EXPECT_EQ(isbn, book.isbn());
  EXPECT_EQ(title, book.title());
}
