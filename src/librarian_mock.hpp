#pragma once

#include "database_mock.hpp"
#include "librarian.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

class MockLibrarian : public Lib::Librarian {
 public:
  using RecognizeResult = std::pair<Lib::Reader, bool>;

  explicit MockLibrarian(
      std::unique_ptr<Lib::Database> db = std::make_unique<MockDatabase>())
      : Lib::Librarian{std::move(db)} {}

  MOCK_METHOD(RecognizeResult, recognize, (std::string name), (override));
};