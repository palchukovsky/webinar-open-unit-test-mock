cmake_minimum_required(VERSION 3.14)

project(Library CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)



# ##############################################################################
# Required libs
#
find_package(libpqxx CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

# ##############################################################################
# Application
#
add_library(lib STATIC
  src/fwd.hpp
  src/book.hpp
  src/database.hpp
  src/pqdatabase.cpp src/pqdatabase.hpp
  src/reader.hpp
  src/request.cpp src/request.hpp
  src/librarian.cpp src/librarian.hpp)
target_link_libraries(lib PUBLIC libpqxx::pqxx)

add_executable(term src/main.cpp)
target_link_libraries(term PRIVATE lib)

# ##############################################################################
# Simpe tests without framework
#
add_executable(tests_simple src/book_test_simple.cpp)
target_link_libraries(tests_simple PRIVATE lib)

# ##############################################################################
# Tests with GTest
#
add_executable(tests
  src/main_test.cpp
  src/book_test.cpp
  src/reader_test.cpp
  src/request_test.cpp
  src/librarian_test.cpp)
target_link_libraries(tests
  PRIVATE
  lib
  GTest::gmock_main)  # GTest::gtest GTest::gtest_main GTest::gmock_main

add_test(tests tests)