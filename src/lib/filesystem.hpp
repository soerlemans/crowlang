#ifndef ACRIS_LIB_FILESYSTEM_HPP
#define ACRIS_LIB_FILESYSTEM_HPP

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
auto temporary_directory() -> path;
} // namespace lib

#endif // ACRIS_LIB_FILESYSTEM_HPP
