#include "settings.hpp"

// STL Includes:
#include <exception>

// Absolute Includes:
#include "crow/debug/log.hpp"
#include "crow/settings/cli.hpp"
#include "crow/settings/toml.hpp"
#include "lib/stdprint.hpp"

namespace settings {
auto get_settings(CLI::App& t_app, const int t_argc, char* t_argv[]) -> Settings
{
  using debug::LogLevel;
  using debug::set_loglevel;

  Settings settings{};

  // Reading of settings happens before setting the loglevel.
  // So for now we should set it, to log config reading.
  set_loglevel(LogLevel::VERBOSE);

  // try {
  //  If a project settings file was found we should use it.
  const auto opt{find_settings_toml()};
  if(opt) {
    const auto path{opt.value()};

    read_settings_toml(path, settings);
  }

  // CLI settings overwrite TOML settings.
  read_cli_settings(t_app, t_argc, t_argv, settings);
  //} catch(std::exception& e) {
  // TODO: Will I use this?
  // }

  DBG_PRINTLN("Settings: ", settings);

  return settings;
}
} // namespace settings

// Functions:
auto operator<<(std::ostream& t_os, const settings::Settings& t_settings)
  -> std::ostream&
{
  // Needed for std print.
  using namespace lib::stdprint::vector;

  t_os << "Settings{ ";
  t_os << "paths: " << t_settings.m_paths << ", ";
  t_os << "bindings: " << t_settings.m_bindings << ", ";
  t_os << "loglevel: " << t_settings.m_level << ", ";
  t_os << '}';

  return t_os;
}
