#ifndef CONFIG_HPP
#define CONFIG_HPP

// STL Includes:
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>

// Absolute Includes:
#include "crow/codegen/backend_interface.hpp"
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
  using BackendType = codegen::BackendType;
  using LogLevel = debug::LogLevel;

  FileVec m_paths;

  codegen::BackendType m_backend;
  StringVec m_bindings;

  debug::LogLevel m_level;

  // Methods:
  Settings()
    : m_paths{},
      m_backend{BackendType::CPP_BACKEND},
      m_bindings{},
      m_level{LogLevel::VERBOSE}
  {}

  Settings(const Settings&) = default;


  // Operators:
  auto operator=(Settings&&) noexcept -> Settings& = default;

  virtual ~Settings() = default;
};

// Functions:
//! Read compiler settings from CLI options or project.toml.
auto get_settings(CliParams& t_params) -> Settings;
} // namespace settings

// Functions:
auto operator<<(std::ostream& t_os, const settings::Settings& t_settings)
  -> std::ostream&;

#endif // CONFIG_HPP
