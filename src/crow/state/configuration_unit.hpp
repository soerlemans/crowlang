#ifndef CROW_CROW_STATE_CONFIGURATION_UNIT_HPP
#define CROW_CROW_STATE_CONFIGURATION_UNIT_HPP

// STL Includes:
#include <memory>
#include <string>
#include <vector>

namespace state {
// Forward Declarations:
class ConfigurationUnit;

// Aliases:
using BackendNameVec = std::vector<std::string>;
using ConfigurationUnitPtr = std::shared_ptr<ConfigurationUnit>;

// Structs:
struct Config {
  BackendNameVec m_backends;
};

// Classes:
/*!
 * Stores the configuration for each @ref TranslationUnit.
 * This includes which backends to use.
 */
class ConfigurationUnit {
  private:
  Config m_config;

  public:
  ConfigurationUnit();

  virtual ~ConfigurationUnit() = default;
};

// Functions:
//! Resolve CLI settings and configuration from project.toml.
auto make_configuration_unit() -> ConfigurationUnitPtr;
} // namespace state

#endif // CROW_CROW_STATE_CONFIGURATION_UNIT_HPP
