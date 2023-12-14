#pragma once

#include "fwd.hpp"

#include <iosfwd>

namespace Lib {

void handle_request(Librarian &librarian, std::istream &in, std::ostream &out);

}