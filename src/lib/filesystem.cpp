#include "filesystem.hpp"

namespace lib {
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
