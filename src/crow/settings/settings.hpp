#ifndef CONFIG_HPP
#define CONFIG_HPP

// STL Includes:
#include <filesystem>
#include <sstream>
#include <vector>

// Absolute Includes:
#include "crow/debug/loglevel.hpp"

namespace settings {
// Aliases:
namespace fs = std::filesystem;
using SourceFiles = std::vector<fs::path>;

// Structs:
struct Settings {
  SourceFiles m_paths;
  debug::LogLevel m_level;

  // Methods:
  Settings(): m_paths{}, m_level{debug::LogLevel::VERBOSE}
  {}

  Settings(const Settings&) = default;


  // Operators:
  auto operator=(Settings&&) noexcept -> Settings& = default;

  virtual ~Settings() = default;
};

// Functions:
//! Read compiler settings from CLI options or project.toml.
auto get_settings() -> Settings;
} // namespace settings

// Functions:
auto operator<<(std::ostream& t_os, const settings::Settings& t_settings)
  -> std::ostream&;

#endif // CONFIG_HPP
