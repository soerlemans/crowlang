#ifndef CROW_CROW_CONFIG_TOML_HPP
#define CROW_CROW_CONFIG_TOML_HPP

// STL Includes:
#include <filesystem>
#include <optional>
#include <string_view>

// Library Includes:
#include <toml++/toml.hpp>

namespace settings {
// Forward Declarations:
struct Settings;

// Using Statements:
using namespace std::literals::string_view_literals;

// Aliases:
namespace fs = std::filesystem;

using PathOpt = std::optional<fs::path>;

// Globals:
//! Name of the TOML file.
constexpr auto settings_toml{"crow.toml"sv};

// Functions:
auto find_settings_toml(const std::string_view t_filename = settings_toml)
  -> PathOpt;
auto read_settings_toml(const fs::path t_filepath) -> Settings;
} // namespace settings

#endif // CROW_CROW_CONFIG_TOML_HPP
