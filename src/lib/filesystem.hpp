#ifndef CROW_LIB_FILESYSTEM_HPP
#define CROW_LIB_FILESYSTEM_HPP

// STL Includes:
#include <filesystem>

// Library Includes:
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>

namespace lib {
// Using Declarations:
using std::filesystem::path;

// Functions:
/**
 * @brief Creates a temporary directory and returns its path.
 *
 * @return Path to temporary directory.
 */
[[nodiscard("Returned temporary directory path must be used.")]]
auto temporary_directory() -> path
{
  namespace b_fs = boost::filesystem;

  // Get path to temporary directory and generate random path.
  const auto tmp_dir_path{b_fs::temp_directory_path()};
  const auto rand_path{b_fs::unique_path()};

  // Create temporary directory.
  const auto tmp_dir{tmp_dir_path / rand_path};
  b_fs::create_directories(tmp_dir);

  return path{tmp_dir.native()};
}
} // namespace lib

#endif // CROW_LIB_FILESYSTEM_HPP
