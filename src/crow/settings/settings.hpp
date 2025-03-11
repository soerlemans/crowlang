#ifndef CONFIG_HPP
#define CONFIG_HPP

// STL Includes:
#include <filesystem>
#include <sstream>
#include <vector>

// Absolute Includes:
#include "crow/debug/loglevel.hpp"

namespace settings {
// Structs:
struct Settings {
  std::vector<std::filesystem::path> m_paths;
  debug::LogLevel m_level;

  Settings(): m_paths{}, m_level{debug::LogLevel::VERBOSE}
  {}
};


} // namespace settings

#endif // CONFIG_HPP
