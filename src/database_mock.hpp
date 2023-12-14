#pragma once

#include "book.hpp"
#include "database.hpp"
#include "reader.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

class MockDatabase : public Lib::Database {
 public:
  MOCK_METHOD(void, insertBook, (const Lib::Book &book), (override));
  MOCK_METHOD(void, updateBook, (const Lib::Book &book), (override));
  MOCK_METHOD(void, deleteBook, (const Lib::Book &book), (override));

  MOCK_METHOD(Lib::Reader, insertReader, (std::string_view name), (override));
  MOCK_METHOD(std::optional<Lib::Reader>,
              findReader,
              (std::string name),
              (const override));

  MOCK_METHOD(std::vector<Lib::Book>, getAllBooks, (), (const override));

  MOCK_METHOD(std::optional<Lib::Book>,
              findBookByTitle,
              (std::string_view title),
              (const override));
  MOCK_METHOD(std::optional<Lib::Book>,
              findBookByIsdn,
              (std::string_view title),
              (const override));

  MOCK_METHOD(std::vector<Lib::Book>,
              findBorrowed,
              (const Lib::Reader &),
              (const override));

  MOCK_METHOD(bool,
              borrowBook,
              (const Lib::Book &, const Lib::Reader &),
              (override));
  MOCK_METHOD(void,
              returnBook,
              (const Lib::Book &, const Lib::Reader &),
              (override));
};