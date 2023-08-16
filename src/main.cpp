// Library Includes:
#include <CLI/App.hpp>
#include <CLI/CLI.hpp>
#include <CLI/Validators.hpp>

// Includes:
#include "debug/log.hpp"
#include "debug/log_macros.hpp"
#include "token/token.hpp"

// Local Includes:
#include "version.hpp"


auto parse_args(CLI::App& t_app, const int t_argc, char* t_argv[]) -> void
{
  t_app.failure_message(CLI::FailureMessage::help);

  // Version flag
  std::stringstream ss;
  ss << "Version: " << NEWLANG_VERSION;
  t_app.set_version_flag("-v,--version", ss.str(), "Show compiler version");

  t_app.parse(t_argc, t_argv);
}

auto main(int t_argc, char* t_argv[]) -> int
{
  CLI::App app{""};

  DBG_SET_LOGLEVEL(INFO);
  try {
    parse_args(app, t_argc, t_argv);
  } catch(const CLI::ParseError& e) {
    return app.exit(e);
  }
}
