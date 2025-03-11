#include "settings.hpp"

namespace settings {
auto get_settings() -> Settings
{
  Settings settings{};

  // TODO: Get CLI settings.
  // TODO: Get settings from TOML file.

  return settings;
}

} // namespace settings
