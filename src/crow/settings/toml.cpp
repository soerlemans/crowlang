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

// Internal:
namespace {
// TODO:
// Helper function for converting a typename to the right comparison.
// constexpr auto

/*!
 * Helper function for extracting a TOML array that is the same type.
 * For now assume that every item is an array.
 */
template<typename NodeType, typename VecType>
auto toml_extract_array(toml::node_view<NodeType>&& t_node,
                        std::vector<VecType>& t_vector,
                        const bool t_required = false) -> void
{
  if(toml::array* arr = t_node.as_array(); arr) {
    const auto lambda{[&](auto&& t_elem) noexcept {
      if constexpr(toml::is_string<decltype(t_elem)>) {
        auto elem{t_elem.get()};

        DBG_INFO("Toml extracted: ", elem);
        t_vector.push_back(elem);
      } else {
        DBG_WARNING("Non string value in toml array.");
      }
    }};

    arr->for_each(lambda);
  } else {
    DBG_WARNING("Toml array does not exist");
  }
}
} // namespace

// Functions:
auto toml_project_section(toml::table& t_table, Settings& t_settings) -> void
{
  using toml::is_string;

  auto project{t_table["project"]};

  toml_extract_array(project["sources"], t_settings.m_paths);
  toml_extract_array(project["bindings"], t_settings.m_bindings);
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

auto read_settings_toml(const fs::path t_filepath, Settings& t_settings) -> void
{
  using toml::parse_error;
  using namespace std::literals;

  try {
    auto table{toml::parse_file(t_filepath.native())};

    toml_project_section(table, t_settings);
    toml_debug_section(table, t_settings);

    // config["project"]["sources"]
    //  std::cout << config["debug"]["loglevel"].value_or("empty"sv);
  } catch(const parse_error& err) {
    const auto description{err.description()};

    DBG_ERROR("Failed to parse ", t_filepath, " results in ", description);

    // Rethrow the error to handle properly.
    throw err;
  }
}
} // namespace settings
