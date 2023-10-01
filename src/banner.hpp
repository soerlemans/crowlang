#ifndef BANNER_HPP
#define BANNER_HPP

// Includes:
#include "debug/log.hpp"


std::array banner = {"                                                \n"
                     "   █████████                                    \n"
                     "  ███▒▒▒▒▒███                                   \n"
                     " ███     ▒▒▒  ████████   ██████  █████ ███ █████\n"
                     "▒███         ▒▒███▒▒███ ███▒▒███▒▒███ ▒███▒▒███ \n"
                     "▒███          ▒███ ▒▒▒ ▒███ ▒███ ▒███ ▒███ ▒███ \n"
                     "▒▒███     ███ ▒███     ▒███ ▒███ ▒▒███████████  \n"
                     " ▒▒█████████  █████    ▒▒██████   ▒▒████▒████   \n"
                     "  ▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒      ▒▒▒▒▒▒     ▒▒▒▒ ▒▒▒▒    \n"
                     "                                                \n"};

auto print_banner() -> void
{
  using namespace debug;

  for(auto& line : banner) {
    print(line);
  }
}

#endif // BANNER_HPP
