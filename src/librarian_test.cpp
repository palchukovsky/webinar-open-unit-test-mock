
#include "database_mock.hpp"
#include "librarian.hpp"

#include <gtest/gtest.h>

using namespace std::literals;
using ::testing::Return;
using namespace Lib;

TEST(LibrarianTest, GetAllBooks) {
  const std::vector<Book> expectedBooks = {{"1", "Death Note part 1"},
                                           {"2", "Death Note part 2"}};

  auto database = std::make_unique<MockDatabase>();
  EXPECT_CALL(*database, getAllBooks()).WillOnce(Return(expectedBooks));

  const auto books = Librarian{std::move(database)}.getAllBooks();

  ASSERT_EQ(expectedBooks.size(), books.size());
  for (size_t i = 0; i < books.size(); ++i) {
    EXPECT_EQ(expectedBooks[i], books[i]) << " at index " << i;
  }
}

TEST(LibrarianTest, Recognize) {
  const auto readerName = "John Doe";
  const Lib::Reader expectedReader{999, readerName};

  auto database = std::make_unique<MockDatabase>();
  EXPECT_CALL(*database, findReader(readerName))
      .WillOnce(Return(expectedReader));

  const auto [reader, found] =
      Librarian{std::move(database)}.recognize(readerName);

  EXPECT_TRUE(found);
  EXPECT_EQ(expectedReader, reader);
}

TEST(LibrarianTest, RecognizeAny) {
  const Lib::Reader expectedReader{999, "John Doe"};

  auto database = std::make_unique<MockDatabase>();
  EXPECT_CALL(*database, findReader(testing::_))
      .Times(testing::AtLeast(1))
      .WillRepeatedly(
          testing::Invoke([&expectedReader](const std::string &name) {
            // std::cout << "Looking for the name: " << name << std::endl;
            return expectedReader;
          }));

  const auto [reader, found] =
      Librarian{std::move(database)}.recognize("Nobody");

  EXPECT_TRUE(found);
  EXPECT_EQ(expectedReader, reader);
}
