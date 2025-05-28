#include "toml.hpp"

// STL Includes:
#include <filesystem>
#include <string_view>

// Absolute Includes:
#include "crow/debug/log.hpp"
#include "crow/settings/enum_convert.hpp"
#include "crow/settings/settings.hpp"

// Internal:
namespace {
// TODO:
// Helper function for converting any toml value to string.
// constexpr auto

/*!
 * Helper function for extracting a TOML array that is the same type.
 * For now assume that every item is an array.
 */
template<typename NodeType, typename VecType>
auto toml_extract_array(toml::node_view<NodeType>&& t_node,
                        std::vector<VecType>& t_vector) -> void
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

namespace settings {
// Aliases:
namespace fs = std::filesystem;

// Functions:
auto toml_project_section(toml::table& t_table, Settings& t_settings) -> void
{
  using namespace std::literals;
  using toml::is_string;

  auto project{t_table["project"]};

  toml_extract_array(project["sources"], t_settings.m_paths);

  // t_settings.m_backend = project["backend"].value_or("cpp"sv);
  if(auto backend{t_table["backend"].value<std::string>()}; backend) {
    t_settings.m_backend = str2backendtype(backend.value());
  }

  toml_extract_array(project["interop_backends"],
                     t_settings.m_interop_backends);
}

auto toml_debug_section(toml::table& t_table, Settings& t_settings) -> void
{
  auto debug{t_table["debug"]};
}
} // namespace settings

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
