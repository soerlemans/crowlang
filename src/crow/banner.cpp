#include "banner.hpp"

auto make_banner() -> std::string
{
  using namespace rang;

  std::stringstream ss;

  std::size_t index{0}, line_index{0};
  while(index < g_banner.size() && line_index < g_banner[index].size()) {
    const auto& letter{g_banner[index]};
    const auto& line{letter[line_index]};

    // Color the C with a blue color
    const auto color{(index == 0) ? fg::blue : fg::reset};

    ss << color << line;

    index++;
    if(index >= g_banner.size()) {
      index = 0;
      line_index++;
    }
  }

  return ss.str();
}
