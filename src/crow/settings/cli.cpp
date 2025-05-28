#include "cli.hpp"

// STL Includes:
#include <map>
#include <string>

// Library Includes:
#include <rang.hpp>

// Absolute Includes:
#include "crow/codegen/backend_interface.hpp"
#include "crow/settings/enum_convert.hpp"
#include "crow/settings/settings.hpp"

// Internal:
namespace {
// Using Statements:
using settings::Settings;

// Functions:
auto add_positional_flags(CLI::App& t_app, Settings& t_settings) -> void
{
  // Program source files:
  t_app.add_option("{}", t_settings.m_paths, "Files to compile.")
    ->check(CLI::ExistingFile);
}

auto add_loglevel_flag([[maybe_unused]] CLI::App& t_app, Settings& t_settings)
  -> void
{
#ifdef DEBUG
  using settings::loglevel_map;
  using settings::LogLevelMap;

  const LogLevelMap& map{loglevel_map()};

  t_app.add_option("-l,--log-level", t_settings.m_level, "Set the LogLevel.")
    ->transform(CLI::CheckedTransformer(map, CLI::ignore_case));
#endif // DEBUG
}

auto add_backend_flag(CLI::App& t_app, Settings& t_settings) -> void
{
  using settings::backendtype_map;
  using settings::BackendTypeMap;

  const BackendTypeMap& map{backendtype_map()};

  t_app
    .add_option("-b,--backend", t_settings.m_backend,
                "Backend to use for code generation.")
    ->transform(CLI::CheckedTransformer(map, CLI::ignore_case));
}

auto add_bindings_flag(CLI::App& t_app, Settings& t_settings) -> void
{

  // TODO: Add map with options.
  t_app.add_option("--bindings", t_settings.m_bindings,
                   "For which languages bindings should be generated for.");
}

auto add_nocolor_flag(CLI::App& t_app) -> void
{
  // Force colors always to be written
  rang::setControlMode(rang::control::Force);

  const auto disable_color{[]() {
    rang::setControlMode(rang::control::Off);
  }};

  t_app.add_flag_callback("--no-color", disable_color,
                          "Disable colored output.");
}

auto add_version_flag(CLI::App& t_app) -> void
{
  // Version flag:
  std::stringstream ss;
  ss << "Version: " << CROW_PROJECT_VERSION;
  t_app.set_version_flag("-v,--version", ss.str(), "Show compiler version");
}
} // namespace

namespace settings {
// Functions:
auto read_cli_settings(CliParams& t_params, Settings& t_settings) -> void
{
  auto& [app, argc, argv] = t_params;

  // Set the formatter.
  auto fmt{std::make_shared<BannerFormatter>()};
  app.formatter(fmt);

  // Add flags:
  add_positional_flags(app, t_settings);

  add_backend_flag(app, t_settings);
  add_bindings_flag(app, t_settings);

  add_loglevel_flag(app, t_settings);
  add_nocolor_flag(app);
  add_version_flag(app);

  app.parse(argc, argv);
}
} // namespace settings
