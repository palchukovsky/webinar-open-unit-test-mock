#include "librarian.hpp"
#include "pqdatabase.hpp"
#include "request.hpp"

#include <exception>
#include <iostream>

using namespace Lib;

int main() {
  try {
    Librarian librarian{std::make_unique<PqDatabase>()};
    handle_request(librarian, std::cin, std::cout);
  } catch (const std::exception &ex) {
    std::cerr << "Unexpected error: " << ex.what() << std::endl;
    return 1;
  }

  return 0;
}