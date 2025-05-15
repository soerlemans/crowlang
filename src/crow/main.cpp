// STL Includes:
#include <fstream>

// Library Includes:
#include <cpptrace/cpptrace.hpp>

// Local Includes:
#include "debug/log.hpp"
#include "settings/settings.hpp"
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

static auto run(settings::Settings t_settings) -> void
{
  using state::TranslationUnit;

  // For now just compile all translation units, sequentially.
  for(const auto& path : t_settings.m_paths) {
    TranslationUnit unit{path};

    unit.execute();
  }
}

//! Log something as an exception.
template<typename T>
inline auto exception(const T t_msg) -> void
{
  using rang::fg;
  using rang::style;

  // Print lovely header.
  std::cerr << style::bold << fg::red << "Exception:\n" << style::reset;

  // Print error message.
  std::cerr << t_msg << std::endl;
}

inline auto uncaught_object() -> void
{
  using rang::fg;
  using rang::style;

  // clang-format off
  std::cerr << style::bold
						<< fg::red
						<< "Uncaught object."
            << style::reset
						<< std::endl;
  // clang-format on
}

// Main:
auto main(const int t_argc, char* t_argv[]) -> int
{
  using settings::get_settings;

  CLI::App app{"Compiler for Crow(lang)"};
  try {
    disable_absorb_exceptions();

    // Retrieve settings (CLI/TOML).
    auto settings{get_settings(app, t_argc, t_argv)};
    debug::set_loglevel(settings.m_level);

    run(settings);
  } catch(CLI::ParseError& e) {
    const auto exit_code{app.exit(e)};
    std::cerr << std::format("CLI11 exit code: {}\n", exit_code);

    return ExitCode::CLI11_EXCEPTION;
  } catch(std::exception& e) {
    exception(e.what());

    return ExitCode::EXCEPTION;
  } catch(...) {
    uncaught_object();

    return ExitCode::EXCEPTION;
  }

  return ExitCode::OK;
}
