#include "settings.hpp"

// STL Includes:
#include <exception>

// Absolute Includes:
#include "crow/debug/log.hpp"
#include "crow/settings/cli.hpp"
#include "crow/settings/toml.hpp"
#include "lib/stdprint.hpp"

namespace settings {
auto get_settings(CliParams& t_params) -> Settings
{
  Settings settings{};

  // try {
  //  If a project settings file was found we should use it.
  const auto opt{find_settings_toml()};
  if(opt) {
    const auto path{opt.value()};

    read_settings_toml(path, settings);
  }

  // CLI settings overwrite TOML settings.
  read_cli_settings(t_params, settings);
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
  t_os << "source_paths: " << t_settings.m_source_paths << ", ";
  t_os << "backend: " << t_settings.m_backend << ", ";
  t_os << "interop_backends: " << t_settings.m_interop_backends << ", ";
  t_os << "loglevel: " << t_settings.m_level << ", ";
  t_os << '}';

  return t_os;
}
