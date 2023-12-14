#pragma once

#include <string>

namespace Lib {

class Reader {
 public:
  Reader(const int id, std::string name) : m_id{id}, m_name{std::move(name)} {}

  bool operator==(const Reader &other) const {
    return m_id == other.m_id && m_name == other.m_name;
  }

  [[nodiscard]] auto id() const { return m_id; }
  [[nodiscard]] auto name() const -> decltype(auto) { return (m_name); }

 private:
  int m_id;
  std::string m_name;
};

}  // namespace Lib