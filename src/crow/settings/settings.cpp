#include "settings.hpp"

// STL Includes:
#include <exception>

// Absolute Includes:
#include "crow/settings/cli.hpp"
#include "crow/settings/toml.hpp"

namespace settings {
auto get_settings(const int t_argc, char* t_argv[]) -> Settings
{
  CLI::App app{"Compiler for Crow(lang)"};
  Settings settings{};

  try {
    // If a project settings file was found we should use it.
    const auto opt{find_settings_toml()};
    if(opt) {
      const auto path{opt.value()};

      settings = read_settings_toml(path);
    }

    // CLI settings overwrite TOML settings.
    settings = read_cli_settings(app, t_argc, t_argv);
  } catch(std::exception& e) {
    // TODO: Will I use this?
  }

  return settings;
}
} // namespace settings

// Functions:
auto operator<<(std::ostream& t_os, const settings::Settings& t_settings)
  -> std::ostream&
{
  t_os << "TODO: Logging settings::Settings.";

  return t_os;
}
