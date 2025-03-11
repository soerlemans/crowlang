#ifndef CROW_CROW_CONFIG_CLI_HPP
#define CROW_CROW_CONFIG_CLI_HPP

// Library Includes:
#include <CLI/App.hpp>
#include <CLI/CLI.hpp>
#include <CLI/Error.hpp>
#include <CLI/Validators.hpp>

// Absolute Includes:
#include "crow/banner.hpp"
#include "crow/definitions.hpp"

// Local Includes:
#include "settings.hpp"

namespace settings {
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
//! Set the CLI arguments to include.
auto cli_args(CLI::App& t_app, const int t_argc, char* t_argv[]) -> Settings;
} // namespace config

#endif // CROW_CROW_CONFIG_CLI_HPP
