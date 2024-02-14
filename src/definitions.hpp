#ifndef CROW_VERSION_HPP
#define CROW_VERSION_HPP

// STL Includes:
#include <string_view>


// Macros:
//! Cmake substitutes the version numbers specified in the root CMakeLists.txt.
#define CROW_PROJECT_VERSION_MAJOR @crow_VERSION_MAJOR @
#define CROW_PROJECT_VERSION_MINOR @crow_VERSION_MINOR @
#define CROW_PROJECT_VERSION_PATCH @crow_VERSION_PATCH @

#define CROW_PROJECT_VERSION "0.4.0"

// TODO: Move elsewhere?
//! Absolute path to the root of the crow project.
#define CROW_PROJECT_ROOT_DIRECTORY "/home/hackerman/crow"

//! Absolute path to the source directory of the crow project
#define CROW_PROJECT_SRC_DIRECTORY "/home/hackerman/crow/src"

//! Convert @ref __FILE__ into a relative path.
#define CROW_PROJECT_RELATIVE_PATH crow::project_relative_path(__FILE__)

namespace crow {
// TODO: Use const char* template parameter?
/*!
 * This function is intended to make the expansion of  @ref __FILE__ macro
 * relative.
 */
constexpr auto project_relative_path(const std::string_view t_file)
  -> std::string_view
{
  // The slash also needs to be stripped.
  constexpr std::string_view src_dir{CROW_PROJECT_SRC_DIRECTORY "/"};

  // Check if the path is located in the crow source directory.
  // if constexpr(t_file.starts_with(src_dir)) {
  // constexpr std::string_view relative_path{t_file.substr(src_dir.size())};
  std::string_view relative_path{t_file.substr(src_dir.size())};

  return relative_path;
  // }

  // return t_file;
}
} // namespace crow

#endif // CROW_PROJECT_VERSION_HPP
