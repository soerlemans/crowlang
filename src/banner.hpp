#ifndef CROW_BANNER_HPP
#define CROW_BANNER_HPP

// STL Includes:
#include <array>
#include <cstddef>
#include <string_view>
#include <type_traits>

// Library Includes:
#include <rang.hpp>

// Includes:
#include "debug/log.hpp"


// Aliases:
using Letter = std::array<std::string_view, 10>;
using Banner = std::array<Letter, 4>;


// Globals:
// clang-format off
Banner g_banner{Letter{"             ",
                       "   █████████ ",
                       "  ███▒▒▒▒▒███",
                       " ███     ▒▒▒ ",
                       "▒███         ",
                       "▒███         ",
                       "▒▒███     ███",
                       " ▒▒█████████ ",
                       "  ▒▒▒▒▒▒▒▒▒  ",
                       "             "},
                Letter{"          ",
                       "          ",
                       "          ",
                       " ████████ ",
                       "▒▒███▒▒███",
                       " ▒███ ▒▒▒ ",
                       " ▒███     ",
                       " █████    ",
                       "▒▒▒▒▒     ",
                       "          "},
                Letter{"         ",
                       "         ",
                       "         ",
                       "  ██████ ",
                       " ███▒▒███",
                       "▒███ ▒███",
                       "▒███ ▒███",
                       "▒▒██████ ",
                       " ▒▒▒▒▒▒  ",
                       "         "},
                Letter{"                \n",
                       "                \n",
                       "                \n",
                       " █████ ███ █████\n",
                       "▒▒███ ▒███▒▒███ \n",
                       " ▒███ ▒███ ▒███ \n",
                       " ▒▒███████████  \n",
                       "  ▒▒████▒████   \n",
                       "   ▒▒▒▒ ▒▒▒▒    \n",
                       "                \n"}};
// clang-format on

//! This is a terrible way to print the banner but it works
auto print_banner() -> void
{
  using namespace rang;
  using namespace debug;

  std::size_t index{0}, line_index{0};
  while(index < g_banner.size() && line_index < g_banner[index].size()) {
    const auto& letter{g_banner[index]};
    const auto& line{letter[line_index]};

		// Color the C with a blue color
    const auto color{(index == 0) ? fg::blue : fg::reset};
    print(color, line);

    index++;
    if(index >= g_banner.size()) {
      index = 0;
      line_index++;
    }
  }
}

#endif // CROW_BANNER_HPP
