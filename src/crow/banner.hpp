#ifndef CROW_CROW_BANNER_HPP
#define CROW_CROW_BANNER_HPP

// STL Includes:
#include <array>
#include <cstddef>
#include <sstream>
#include <string_view>
#include <type_traits>

// Library Includes:
#include <rang.hpp>

// Absolute Includes:
#include "debug/log.hpp"

// TODO: Place into the crow namespace:
// Aliases:
using Letter = std::array<std::string_view, 10>;
using Banner = std::array<Letter, 4>;


// Globals:
// clang-format off
constexpr Banner g_banner{Letter{"             ",
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

// FIXME: Find a more elegant way to print the banner.
auto make_banner() -> std::string;

/*!
 * The banner is printed with color the help page.
 */
// auto print_banner() -> void
// {
//   using namespace rang;
//   using namespace debug;

//   std::size_t index{0}, line_index{0};
//   while(index < g_banner.size() && line_index < g_banner[index].size()) {
//     const auto& letter{g_banner[index]};
//     const auto& line{letter[line_index]};

// 		// Color the C with a blue color
//     const auto color{(index == 0) ? fg::blue : fg::reset};
//     print(color, line);

//     index++;
//     if(index >= g_banner.size()) {
//       index = 0;
//       line_index++;
//     }
//   }
// }

#endif // CROW_CROW_BANNER_HPP
