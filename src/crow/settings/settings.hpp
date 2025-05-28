#ifndef CONFIG_HPP
#define CONFIG_HPP

// STL Includes:
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>

// Absolute Includes:
#include "crow/debug/loglevel.hpp"

// Local Includes:
#include "cli.hpp"
#include "toml.hpp"

namespace settings {
// Aliases:
namespace fs = std::filesystem;
using FileVec = std::vector<fs::path>;
using StringVec = std::vector<std::string>;

// Structs:
struct Settings {
  FileVec m_paths;
  StringVec m_bindings;
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
auto get_settings(CLI::App& t_app, int t_argc, char* t_argv[]) -> Settings;
} // namespace settings

// Functions:
auto operator<<(std::ostream& t_os, const settings::Settings& t_settings)
  -> std::ostream&;

#endif // CONFIG_HPP
