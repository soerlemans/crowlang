#include "banner.hpp"

// STL Includes:
#include <array>
#include <cstddef>
#include <sstream>
#include <string_view>
#include <type_traits>
#include <variant>

// Library Includes:
#include <rang.hpp>


/*!
 * @file
 *
 * This file contains the utilities for printing the banner of acris.
 */

// Macros:
#define STYLE(t_style) {.m_style = style::t_style}

#define FG(t_color) {.m_fg = fg::t_color}

#define BG(t_color) {.m_bg = bg::t_color}

#define FGB(t_color) {.m_fg = fgB::t_color}

#define BGB(t_color) {.m_bg = bgB::t_color}


// Forward Declarations:
struct Section;

// Using Statements:
using rang::bg;
using rang::bgB;
using rang::fg;
using rang::fgB;
using rang::style;

// Aliases:
using Fg = std::variant<fg, fgB>;
using Bg = std::variant<bg, bgB>;

using Row = std::array<Section, 4>;
using Banner = std::array<Row, 20>;

// Enums:
/*!
 * Here are the indexes of the Sections.
 */
enum class BannerColumn : std::size_t {
  C = 0,
  ROW,
  CAW_CAW,
  LOGO
};

// Structs:
struct RangConfig {
  style m_style{style::reset};
  Fg m_fg{fg::reset};
  Bg m_bg{bg::reset};
};

struct Section {
  RangConfig m_cfg;
  std::string_view m_text;

  Section(const std::string_view t_text): m_cfg{}, m_text{t_text}
  {}

  Section(RangConfig&& t_cfg, const std::string_view t_text)
    : m_cfg{std::move(t_cfg)}, m_text{t_text}
  {}
};

namespace {
// Aliases:
// We define the following aliases to save column width:
using S = Section;
using R = Row;

// Globals:
// clang-format off
/*!
 * The banner is a per section colored matrix of characters.
 * In order to keep the banner readable.
 * It has bin split into
 */
//constexpr Banner g_banner{
const Banner g_banner{
R{S{          "             "}, S{          "                                   "}, S{            "          "}, S{FG(blue), "                          .@@@    @@@@@         \n"}},
R{S{FG(blue), "   █████████ "}, S{          "                                   "}, S{            "          "}, S{FG(blue), "                         @@@@@@ @@@@@@@@@       \n"}},
R{S{FG(blue), "  ███▒▒▒▒▒███"}, S{          "                                   "}, S{            "          "}, S{FG(blue), "                        /@@@@@@@@@@@@@@@@       \n"}},
R{S{FG(blue), " ███     ▒▒▒ "}, S{          " ████████   ██████  █████ ███ █████"}, S{            "          "}, S{FG(blue), "         (@@@@@@@@&     /@@@@@@@@@@@@@@@@@@@    \n"}},
R{S{FG(blue), "▒███         "}, S{          "▒▒███▒▒███ ███▒▒███▒▒███ ▒███▒▒███ "}, S{            "          "}, S{FG(blue), "       @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ \n"}},
R{S{FG(blue), "▒███         "}, S{          " ▒███ ▒▒▒ ▒███ ▒███ ▒███ ▒███ ▒███ "}, S{FG(yellow), "  Caw caw~"}, S{FG(blue), "      @@@*&@@@@@*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"}},
R{S{FG(blue), "▒▒███     ███"}, S{FG(blue), " ▒███     ▒███ ▒███ ▒▒███████████  "}, S{            "          "}, S{FG(blue), "    (@@@@@@@..@@@@@@@@@@@(((((((((@@@@@@@@@@@@@ \n"}},
R{S{FG(blue), " ▒▒█████████ "}, S{FG(blue), " █████    ▒▒██████   ▒▒████▒████   "}, S{            "          "}, S{FG(blue), "  /(&@@@@@@.@@@@@@@@@@@((((((((((((((@@         \n"}},
R{S{FG(blue), "  ▒▒▒▒▒▒▒▒▒  "}, S{FG(blue), "▒▒▒▒▒      ▒▒▒▒▒▒     ▒▒▒▒ ▒▒▒▒    "}, S{            "          "}, S{FG(blue), "  ((@@@@@@@@@@@@@@@@@@(((((((((((((((((         \n"}},
R{S{          "             "}, S{          "                                   "}, S{            "          "}, S{FG(blue), " (((@@@@@@@@@@@@@@@@@@((((((((((((((((((        \n"}},
R{S{          "             "}, S{          "                                   "}, S{            "          "}, S{FG(blue), " (((@@@@@@@@@@@@@@@@@@(((((((((((((((((((       \n"}},
R{S{          "             "}, S{          "                                   "}, S{            "          "}, S{FG(blue), "  ((@@@@@@@@@@@@@@@@@@@((((((((((((((((((       \n"}},
R{S{          "             "}, S{          "                                   "}, S{            "          "}, S{FG(blue), "   (@@@@@@@@@@@@@@@@@@@@@((((((((((((((((       \n"}},
R{S{          "             "}, S{          "                                   "}, S{            "          "}, S{FG(blue), "      @@@@@@@@@@@@@@@@@@@@@@@@@@                \n"}},
R{S{          "             "}, S{          "                                   "}, S{            "          "}, S{FG(blue), "        @@@@@@@@@@@@@@@@@@@@@                   \n"}},
R{S{          "             "}, S{          "                                   "}, S{            "          "}, S{FG(blue), "            .@@@@@@@@@@@%   .@                  \n"}},
R{S{          "             "}, S{          "                                   "}, S{            "          "}, S{          "                    @        &@                 \n"}},
R{S{          "             "}, S{          "                                   "}, S{            "          "}, S{          "                   @@        @                  \n"}},
R{S{          "             "}, S{          "                                   "}, S{            "          "}, S{          "                 @. ,     *@@@                  \n"}},
R{S{          "             "}, S{          "                                   "}, S{            "          "}, S{          "                           %                    \n"}}
};

// clang-format on

/*!
 * Apply rang options.
 */
auto operator<<(std::ostream& t_os, const RangConfig& t_cfg) -> std::ostream&
{
  const auto& [style, fg, bg] = t_cfg;

  const auto print{[&](auto&& t_v) {
    t_os << t_v;
  }};

  t_os << style;

  // These are variants so we need to visit them.
  std::visit(print, fg);
  std::visit(print, bg);

  return t_os;
}

auto operator<<(std::ostream& t_os, const Section& t_section) -> std::ostream&
{
  const auto& [rang_cfg, text] = t_section;

  t_os << rang_cfg << text;

  return t_os;
}
} // namespace

// Functions:
auto make_banner() -> std::string
{
  std::stringstream ss;

  for(const auto& row : g_banner) {
    for(std::size_t index{0}; index < row.size(); index++) {
      const auto section{row[index]};

      ss << section;
    }
  }

  ss << fg::reset;

  return ss.str();
}
