// STL Includes:
#include <filesystem>
#include <fstream>

// Library Includes:
#include <CLI/App.hpp>
#include <CLI/CLI.hpp>
#include <CLI/Validators.hpp>

// Includes:
#include "container/text_buffer.hpp"
#include "debug/log.hpp"
#include "debug/log_macros.hpp"
#include "lexer/lexer.hpp"
#include "token/token.hpp"

// Local Includes:
#include "version.hpp"


// Aliases:
namespace fs = std::filesystem;

// Enums:
enum ExitCode {
  OK = 0,
  IMPROPER_USAGE,
  EXCEPTION = 100,
  SIGNAL,
};

// Globals:
struct Settings {
  std::vector<fs::path> m_filepaths;
} settings;

// Functions:
auto parse_args(CLI::App& t_app, const int t_argc, char* t_argv[]) -> void
{
  t_app.failure_message(CLI::FailureMessage::help);

  // Program files
  t_app.add_option("{}", settings.m_filepaths, "Postional arguments")
    ->check(CLI::ExistingFile);

  // Version flag
  std::stringstream ss;
  ss << "Version: " << NEWLANG_VERSION;
  t_app.set_version_flag("-v,--version", ss.str(), "Show compiler version");


  t_app.parse(t_argc, t_argv);
}

auto open_file(const fs::path t_path) -> container::TextBuffer
{
  using namespace container;

  TextBuffer tb;

  if(!fs::exists(t_path)) {
    std::stringstream ss;
    ss << "File does not exist! ";
    ss << std::quoted(t_path.string());

    throw std::invalid_argument{ss.str()};
  }

  std::ifstream ifs{t_path};
  while(ifs.good() && !ifs.eof()) {
    std::string line;
    std::getline(ifs, line);

    // Dont discard newlines
    line += '\n';

    tb.add_line(line);
  }

  return tb;
}


auto run() -> void
{
  using namespace container;

  for(const auto& filepath : settings.m_filepaths) {
		DBG_PRINTLN("=== LEXING ===");
    auto tb_ptr{std::make_shared<TextBuffer>(open_file(filepath))};
    lexer::Lexer lexer{tb_ptr};

		lexer.tokenize();
  }
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

  run();
}
