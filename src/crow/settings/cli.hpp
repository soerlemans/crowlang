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

namespace settings {
// Forward Declarations:
struct Settings;

// Structs:
/*!
 * Utility struct for passing around the parameters needed.
 * To get the CLI parameters.
 *
 * @note
 */
struct CliParams {
  CLI::App m_app;
  int m_argc;
  char** m_argv;
};

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
auto read_cli_settings(CliParams& t_params, Settings& t_settings) -> void;
} // namespace settings

#endif // CROW_CROW_CONFIG_CLI_HPP
