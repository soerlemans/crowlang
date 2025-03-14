// STL Includes:
#include <fstream>

// Library Includes:
#include <cpptrace/cpptrace.hpp>

// Local Includes:
#include "cli.hpp"
#include "debug/log.hpp"
#include "state/translation_unit.hpp"

// Enums:
enum ExitCode {
  OK = 0,
  IMPROPER_USAGE,
  EXCEPTION = 100,
  SIGNAL = 200,
  CLI11_EXCEPTION = 300,
};

// TODO: Relocate.
static auto disable_absorb_exceptions() -> void
{
#ifdef DEBUG
  // Do not absorb cpptrace errors on debug build.
  cpptrace::absorb_trace_exceptions(false);
#endif
}

static auto run() -> void
{
  using state::TranslationUnit;

  // For now just compile all translation units, sequentially.
  for(const auto& path : settings.m_paths) {
    TranslationUnit unit{path};

    unit.execute();
  }
}

// Main:
auto main(const int t_argc, char* t_argv[]) -> int
{
  using rang::fg;
  using rang::style;

  // Initialize command line argument parser.
  CLI::App app{"Compiler for Crow(lang)"};
  try {
    disable_absorb_exceptions();
    cli_args(app, t_argc, t_argv);
    // Set loglevel.
    debug::set_loglevel(settings.m_level);
  } catch(const CLI::ParseError& e) {
    const auto exit_code{CLI11_EXCEPTION + app.exit(e)};

    return exit_code;
  }

  try {
    run();
  } catch(std::exception& e) {
    std::cerr << style::bold << " - ";
    std::cerr << fg::red << "EXCEPTION";
    std::cerr << fg::reset << " - \n" << style::reset;

    // Print error message:
    std::cerr << e.what() << std::endl;

    return ExitCode::EXCEPTION;
  }

  return ExitCode::OK;
}
