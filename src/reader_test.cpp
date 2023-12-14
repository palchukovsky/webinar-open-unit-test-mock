#include "reader.hpp"

#include <gtest/gtest.h>

#include <string>

using namespace std::literals;
using namespace Lib;

TEST(Reader, Create) {
  const auto id = 1;
  const auto name = "The Best Reader"s;

  const Lib::Reader reader{id, name};

  EXPECT_EQ(id, reader.id());
  EXPECT_EQ(name, reader.name());
}