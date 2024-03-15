#include "cli.hpp"


// External globals:
Settings settings;

// Functions:
auto parse_args(CLI::App& t_app, const int t_argc, char* t_argv[]) -> void
{
  // Set the formatter.
  auto fmt{std::make_shared<BannerFormatter>()};
  t_app.formatter(fmt);

  // Program source files:
  t_app.add_option("{}", settings.m_paths, "Files to compile.")
    ->check(CLI::ExistingFile)
    ->required();

  // Force colors always to be written
  rang::setControlMode(rang::control::Force);
  const auto disable_color{[]() {
    rang::setControlMode(rang::control::Off);
  }};
  t_app.add_flag_callback("--no-color", disable_color,
                          "Disable colored output.");

  // Version flag:
  std::stringstream ss;
  ss << "Version: " << CROW_PROJECT_VERSION;
  t_app.set_version_flag("-v,--version", ss.str(), "Show compiler version");

  t_app.parse(t_argc, t_argv);
}
