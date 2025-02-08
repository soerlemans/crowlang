#include "clang_frontend_invoker.hpp"

// STL Includes:
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string_view>

// Local Includes:
#include "crow/debug/log.hpp"
#include "lib/types.hpp"

namespace codegen::cpp_backend {
// Using Statements:
using namespace std::literals::string_view_literals;

// Methods:
ClangFrontendInvoker::ClangFrontendInvoker(): m_compiler_flags{}
{
  // Add debug flags.
  add_flags("-g -ggdb"sv);

  // Add C++23 standard flag.
  add_flags("-std=c++23"sv);
}

auto ClangFrontendInvoker::add_flags(const std::string_view t_str) -> void
{
  // Add spaces passed around the passed flags, automatically.

  // TODO: Sanitize this one day as to prevent command injection.
  // TODO: Maybe also change the escape char for std::quoted()?
  m_compiler_flags << ' ' << t_str << ' ';
}

// Public Methods:
auto ClangFrontendInvoker::compile(const path &t_filepath) -> void
{
  const auto stem{t_filepath.stem()};

  const auto tmp_base{t_filepath.parent_path() / stem};
  auto tmp_obj{tmp_base};
  tmp_obj += ".o";

  auto binary{stem};
  binary += ".out";

  const auto source_str{t_filepath.native()};
  const auto binary_str{binary.native()};

  // Logging:
  DBG_INFO("tmp_obj: ", tmp_obj);
  DBG_INFO("binary: ", binary);

  // Print generated code (lazy implementation).
#ifdef DEBUG
  DBG_PRINTLN("# C++ codegeneration:");

  const auto cmd_cat{
    std::format("clang-format --style=Google < {}", source_str)};
  std::system(cmd_cat.c_str());

  DBG_PRINTLN();
#endif // DEBUG

  DBG_PRINTLN("# Clang Compilation:");

  // TODO: Add -O2 flag on release and reldebug builds (not on debug).
  // FIXME: This is a temporary workaround till the programmatic approach works.

  // List version of compiler used.
  // We use G++ at the moment as it supports more of C++23.
  const auto cpp_compiler{"g++"sv};

  const auto flags{m_compiler_flags.view()};
  const auto cmd{
    std::format("{} {} {} -o {}", cpp_compiler, source_str, flags, binary_str)};

  DBG_NOTICE("Compiler command: ", cmd);
  const auto status_code{std::system(cmd.c_str())};

  if(status_code == 0) {
    DBG_NOTICE("Binary was generated!: ", binary);
  } else {
    DBG_CRITICAL(cpp_compiler, "Failed to compile.");

    // TODO: Throw an exception. Or maybe not?
  }
}
} // namespace codegen::cpp_backend
