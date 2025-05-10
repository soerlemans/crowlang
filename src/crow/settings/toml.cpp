#include "toml.hpp"

// Library Includes:
#include <toml++/toml.hpp>

// Absolute Includes:
#include "crow/debug/log.hpp"

namespace settings {
// Functions:
auto find_settings_toml(const std::string_view t_filename) -> PathOpt
{
  using fs::exists;
  using fs::is_regular_file;

  PathOpt path{};

  const auto filename_quoted{std::quoted(t_filename)};

  fs::path current{fs::current_path()};
  while(true) {
    auto candidate{current / t_filename};
    if(exists(candidate) && is_regular_file(candidate)) {
      DBG_INFO("Found ", filename_quoted, " at ", candidate);
      path = candidate;
      break;
    }

    // Check if we are at the root directory.
    if(current == current.root_path()) {
      DBG_VERBOSE("Could not find ", filename_quoted);
      break;
    }

    // Check parent path in next iteration.
    current = current.parent_path();
  }

  return path;
}

auto read_settings_toml(const fs::path t_filepath) -> Settings
{
  using toml::parse_error;

  Settings settings{};

  try {
    auto config{toml::parse_file(t_filepath.native())};


  } catch(const toml::parse_error& err) {

    const auto filepath_quoted{std::quoted(t_filepath.native())};
    const auto description{err.description()};

    DBG_ERROR("Failed to parse ", filepath_quoted, " results in ", description);

    // Rethrow the error to handle properly.
    throw err;
  }

  return settings;
}
} // namespace settings
