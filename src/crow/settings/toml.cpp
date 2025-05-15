#include "toml.hpp"

// STL Includes:
#include <filesystem>

// Absolute Includes:
#include "crow/debug/log.hpp"

// Local Includes:
#include "settings.hpp"

// Internal:
namespace {
// Using Statements:
using namespace settings;

// Aliases:
namespace fs = std::filesystem;

// Functions:
auto toml_project_section(toml::table& t_table, Settings& t_settings) -> void
{
  using toml::is_string;

  auto project{t_table["project"]};
  auto* sources{project["sources"].as_array()};

  if(sources) {
    const auto lambda{[&](auto&& t_elem) noexcept {
      if constexpr(is_string<decltype(t_elem)>) {
        // Insert paths to source files.
        auto& paths{t_settings.m_paths};
        auto path{t_elem.get()};

        DBG_INFO("Compilation path added: ", path);
        paths.push_back(path);
      } else {
        DBG_WARNING("Non string value in array.");
      }
    }};

    sources->for_each(lambda);
  } else {
    DBG_INFO("TOML path project.sources non existent.");
  }
}

auto toml_debug_section(toml::table& t_table, Settings& t_settings) -> void
{
  auto debug{t_table["debug"]};
}
} // namespace

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
  using namespace std::literals;

  Settings settings{};

  try {
    auto table{toml::parse_file(t_filepath.native())};

    toml_project_section(table, settings);
    toml_debug_section(table, settings);

    // config["project"]["sources"]
    //  std::cout << config["debug"]["loglevel"].value_or("empty"sv);
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
