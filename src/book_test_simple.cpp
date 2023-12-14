#include "book.hpp"

#include <cassert>
#include <iostream>
#include <string>

using namespace std::literals;
using namespace Lib;

void testBookCreation() {
  const auto isbn = "978-3-16-148410-0"s;
  const auto title = "Death Note"s;

  const Lib::Book book{isbn, title};

  assert(isbn == book.isbn());
  assert(title == book.title());

  std::clog << "Book creation: OK\n";
}

// -----------------------------------------------------------------------------

auto main() -> int {
  try {
    testBookCreation();
  } catch (...) {
    std::cerr << "Some tests has been FAILED!\n";
    return 1;
  }

  std::cout << "All test are OK!\n";
  return 0;
}