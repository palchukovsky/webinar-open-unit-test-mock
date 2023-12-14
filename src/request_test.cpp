#include "librarian_mock.hpp"
#include "reader.hpp"
#include "request.hpp"

using namespace std::literals;
using ::testing::Return;
using namespace Lib;

TEST(RequestTest, UserName) {
  const auto readerName = "John Doe";
  const Reader expectedReader = {55, "John Doe 2"};

  std::istringstream in("John Doe\n1\n0\n");
  std::ostringstream out;

  MockLibrarian librarian;
  EXPECT_CALL(librarian, recognize("John Doe"))
      .WillOnce(testing::Return(std::make_pair(expectedReader, false)));

  handle_request(librarian, in, out);

  const auto output = out.str();
  EXPECT_THAT(output, testing::HasSubstr("Enter your name: "));
  EXPECT_THAT(output, testing::HasSubstr("Nice to meet you, "));
  EXPECT_THAT(output, testing::HasSubstr("Your ID is "));
  EXPECT_THAT(output, testing::HasSubstr("Actions:"));
}