#ifndef TEMPORARY_DIRECTORY_HPP
#define TEMPORARY_DIRECTORY_HPP

// STL Includes:
#include <boost/filesystem/operations.hpp>
#include <filesystem>

// Library Includes:
#include <boost/filesystem.hpp>

namespace lib {
// Namespace aliases:
namespace fs = std::filesystem;

/**
 * @brief Creates a temporary directory and returns its path.
 *
 * @return Path to temporary directory.
 */
[[nodiscard("Returned temporary directory path must be used.")]]
auto temporary_directory() -> fs::path
{
  namespace b_fs = boost::filesystem;

  // Get path to temporary directory and generate random path.
  const auto tmp_dir_path{b_fs::temp_directory_path()};
  const auto rand_path{b_fs::unique_path()};

	// Create temporary directory.
  const auto tmp_dir{tmp_dir_path / rand_path};
  b_fs::create_directories(tmp_dir);

  return fs::path{tmp_dir.native()};
}
} // namespace lib

#endif // TEMPORARY_DIRECTORY_HPP
