#include "cli.hpp"

// STL Includes:
#include <map>
#include <string>

// Library Includes:
#include <rang.hpp>

// Internal:
namespace {
// Using Statements:
using settings::Settings;

// Functions:
auto add_loglevel_flag([[maybe_unused]] CLI::App& t_app, Settings& t_settings)
  -> void
{
#ifdef DEBUG
  using debug::LogLevel;

  std::map<std::string, LogLevel> map{};

  // TODO: Write a more elegant implementation later (I was lazy).
  map.insert({"critical", LogLevel::CRITICAL});
  map.insert({"error", LogLevel::ERROR});
  map.insert({"warning", LogLevel::WARNING});
  map.insert({"notice", LogLevel::NOTICE});
  map.insert({"info", LogLevel::INFO});
  map.insert({"verbose", LogLevel::VERBOSE});

  t_app.add_option("-l,--log-level", t_settings.m_level, "Set the LogLevel.")
    ->transform(CLI::CheckedTransformer(map, CLI::ignore_case));
#endif // DEBUG
}

auto add_positional_flags(CLI::App& t_app, Settings& t_settings) -> void
{
  // Program source files:
  t_app.add_option("{}", t_settings.m_paths, "Files to compile.")
    ->check(CLI::ExistingFile)
    ->required();
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
auto cli_args(CLI::App& t_app, const int t_argc, char* t_argv[]) -> Settings
{
  Settings settings{};

  // Set the formatter.
  auto fmt{std::make_shared<BannerFormatter>()};
  t_app.formatter(fmt);

  // Add flags:
  add_positional_flags(t_app, settings);
  add_loglevel_flag(t_app, settings);
  add_nocolor_flag(t_app);
  add_version_flag(t_app);

  t_app.parse(t_argc, t_argv);

  return settings;
}
} // namespace settings
