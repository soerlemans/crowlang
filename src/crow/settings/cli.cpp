#include "cli.hpp"

// STL Includes:
#include <map>
#include <string>

// Library Includes:
#include <rang.hpp>

// Absolute Includes:
#include "crow/codegen/backend_interface.hpp"
#include "crow/debug/debug.hpp"
#include "crow/settings/enum_convert.hpp"
#include "crow/settings/settings.hpp"
#include "lib/iomanip/cond_nl.hpp"

// Internal:
namespace {
// Using Statements:
using settings::Settings;

// Functions:
auto add_positional_flags(CLI::App& t_app, Settings& t_settings) -> void
{
  // Program source files:
  t_app.add_option("{}", t_settings.m_source_paths, "Files to compile.")
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
    ->transform(CLI::CheckedTransformer(map));
#endif // DEBUG
}

auto add_log_multiline_flag([[maybe_unused]] CLI::App& t_app) -> void
{
#ifdef DEBUG

  using namespace lib;

  t_app.add_flag_callback(
    "--log-multiline", iomanip::CondNl::enable,
    "Enable printing objects over multiple lines, when logging.");

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
    ->transform(CLI::CheckedTransformer(map));
}

auto add_bindings_flag(CLI::App& t_app, Settings& t_settings) -> void
{
  using settings::interopbackendtype_map;
  using settings::InteropBackendTypeMap;

  const InteropBackendTypeMap& map{interopbackendtype_map()};

  t_app
    .add_option("-i,--interop", t_settings.m_interop_backends,
                "Which interop backends should be enabled.")
    ->transform(CLI::CheckedTransformer(map));
}

auto add_nocolor_flag(CLI::App& t_app) -> void
{
  // Force colors always to be written (default).
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

auto add_build_subcommand(CLI::App& t_app) -> void
{
  auto* build_subcom{
    t_app.add_subcommand("build", "Compile a project according to crow.toml.")};

  DBG_WARNING("FIXME: Not implemented.");
}

auto add_compile_subcommand(CLI::App& t_app) -> void
{
  auto* compile_subcom{
    t_app.add_subcommand("compile", "Compile a single crow source file.")};

  DBG_WARNING("FIXME: Not implemented.");
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

  // Log specific flags:
  add_loglevel_flag(app, t_settings);
  add_log_multiline_flag(app);

  // Misc. flags:
  add_nocolor_flag(app);
  add_version_flag(app);

  // Subcommands:
  add_build_subcommand(app);
  add_compile_subcommand(app);

  // Parse all set flags.
  app.parse(argc, argv);
}
} // namespace settings
