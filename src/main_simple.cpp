#include "book.hpp"
#include "librarian.hpp"
#include "pqdatabase.hpp"
#include "reader.hpp"
#include "request.hpp"

#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace Lib;

namespace {

auto operator<<(std::ostream &out, const std::vector<Book> &list)
    -> std::ostream & {
  for (const auto &book : list) {
    out << book.title() << " (ISBN: " << book.isbn() << ")\n";
  }
  return out;
}

void borrowBook(Librarian &librarian,
                Reader &user,
                std::istream &in,
                std::ostream &out) {
  out << "Enter book's ISBN: ";
  std::string isbn;
  std::getline(in, isbn);

  const auto [wasFound, wasBorrowed] = librarian.borrowBook(isbn, user);

  if (!wasFound) {
    out << "Unknown book with ISBN " << isbn << ".\n";
    return;
  }
  if (!wasBorrowed) {
    out << "Book with ISBN " << isbn << " is already borrowed, sorry.\n";
    return;
  }

  out << "Book with ISBN " << isbn << " was borrowed by " << user.name()
      << ".\n";
}

void returnBook(Librarian &librarian,
                Reader &user,
                std::istream &in,
                std::ostream &out) {
  out << "Enter book's ISBN: ";
  std::string isbn;
  std::getline(in, isbn);

  const bool wasFound = librarian.returnBook(isbn, user);

  if (!wasFound) {
    out << "Unknown book with ISBN " << isbn << ".\n";
    return;
  }

  out << "Book with ISBN " << isbn << " was returned by " << user.name()
      << ".\n";
}

}  // namespace

int main() {
  std::string userName;
  out << "Enter your name: ";
  std::getline(in, userName);

  auto recognizingResult = librarian.recognize(userName);
  if (recognizingResult.second) {
    out << "You are new in our library!\n";
  }
  auto &user = recognizingResult.first;
  out << "Nice to meet you, " << user.name() << "! Your ID is " << user.id()
      << ".\n";

  for (;;) {
    out << "Actions:\n"
        << "1. Show books\n"
        << "2. Borrow a book\n"
        << "3. Return a book\n"
        << "\nChoose your action: ";

    int action = 0;
    in >> action;
    std::cin.ignore();

    out << "\nResult:\n";

    switch (action) {
      case 1:
        out << librarian.getAllBooks();
        break;
      case 2:
        borrowBook(librarian, user, in, out);
        break;
      case 3:
        returnBook(librarian, user, in, out);
        break;
      default:
        out << "Unknown action, try again.\n";
    }
  }

  return 0;
}