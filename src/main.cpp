// STL Includes:
#include <fstream>

// Local Includes:
#include "phases.hpp"


// Enums:
enum ExitCode {
  OK = 0,
  IMPROPER_USAGE,
  EXCEPTION = 100,
  SIGNAL = 200,
};

// Main:
auto main(int t_argc, char* t_argv[]) -> int
{
  // Initialize command line argument parser.
  CLI::App app{"Compiler for Crow(lang)"};

  // TODO: Relocate?
#ifdef DEBUG
  // Do not absorb cpptrace errors on debug build.
  cpptrace::absorb_trace_exceptions(false);
#endif

  DBG_SET_LOGLEVEL(INFO);
  try {
    parse_args(app, t_argc, t_argv);
  } catch(const CLI::ParseError& e) {
    return -app.exit(e);
  }

  // Set LogLevel to verbose for now
  DBG_SET_LOGLEVEL(VERBOSE);

  try {
    run();
  } catch(std::exception& e) {
    using namespace rang;

    std::cerr << "\n";
    std::cerr << style::bold << " - ";
    std::cerr << fg::red << "EXCEPTION";
    std::cerr << fg::reset << " - \n" << style::reset;

    // Print error message:
    std::cerr << e.what() << std::endl;

    return ExitCode::EXCEPTION;
  }

  return ExitCode::OK;
}
