#ifndef CLI_ARGUMENTS_HPP
#define CLI_ARGUMENTS_HPP

// STL Includes:
#include <filesystem>
#include <sstream>
#include <vector>

// Library Includes:
#include <CLI/App.hpp>
#include <CLI/CLI.hpp>
#include <CLI/Error.hpp>
#include <CLI/Validators.hpp>
#include <rang.hpp>

// Local Includes:
#include "banner.hpp"
#include "version.hpp"

// Aliases:
namespace fs = std::filesystem;

// Globals:
struct Settings {
  std::vector<fs::path> m_paths;
} settings;

// Classes:
class BannerFormatter : public CLI::Formatter {
  public:
  BannerFormatter(): Formatter()
  {}

	//! Add banner to beginning of the description.
  auto make_description(const CLI::App* t_app) const -> std::string override
  {
    std::stringstream ss;

    ss << make_banner();
    ss << CLI::Formatter::make_description(t_app);

    return ss.str();
  }
};

// Functions:
auto parse_args(CLI::App& t_app, const int t_argc, char* t_argv[]) -> void
{
  // Set the formatter.
  auto fmt{std::make_shared<BannerFormatter>()};
  t_app.formatter(fmt);

  // Program source files:
  t_app.add_option("{}", settings.m_paths, "Files to compile.")
    ->check(CLI::ExistingFile);

  // Force colors always to be written
  rang::setControlMode(rang::control::Force);
  const auto disable_color{[]() {
    rang::setControlMode(rang::control::Off);
  }};
  t_app.add_flag_callback("--no-color", disable_color,
                          "Disable colored output.");

  // Version flag:
  std::stringstream ss;
  ss << "Version: " << CROW_VERSION;
  t_app.set_version_flag("-v,--version", ss.str(), "Show compiler version");

  t_app.parse(t_argc, t_argv);
}


#endif // CLI_ARGUMENTS_HPP
