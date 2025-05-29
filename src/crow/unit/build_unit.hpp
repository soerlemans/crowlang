#ifndef CROW_CROW_STATE_CONFIGURATION_UNIT_HPP
#define CROW_CROW_STATE_CONFIGURATION_UNIT_HPP

// STL Includes:
#include <memory>
#include <string>
#include <vector>

namespace state {
// Forward Declarations:
class BuildUnit;

// Aliases:
using BackendNameVec = std::vector<std::string>;
using BuildUnitPtr = std::shared_ptr<BuildUnit>;

// Structs:
struct Config {
  BackendNameVec m_backends;
};

// Classes:
/*!
 * Stores the configuration for each @ref TranslationUnit.
 * This includes which backends to use.
 */
class BuildUnit {
  private:
  Config m_config;

  public:
  BuildUnit();

  virtual ~BuildUnit() = default;
};

// Functions:
//! Resolve CLI settings and configuration from project.toml.
auto make_build_unit() -> BuildUnitPtr;
} // namespace state

#endif // CROW_CROW_STATE_CONFIGURATION_UNIT_HPP
