#ifndef CROW_CROW_STATE_CONFIGURATION_UNIT_HPP
#define CROW_CROW_STATE_CONFIGURATION_UNIT_HPP

// STL Includes:
#include <memory>

namespace state {
// Forward Declarations:
class ConfigurationUnit;

// Aliases:
using ConfigurationUnitPtr = std::shared_ptr<ConfigurationUnit>;

// Classes:
/*!
 * Stores the configuration for each @ref TranslationUnit.
 * This includes which backends to use 
 */
class ConfigurationUnit {
  private:
  public:
  ConfigurationUnit();

  virtual ~ConfigurationUnit();
};

// Functions:
//! Resolve CLI settings and configuration from project.toml.
auto make_configuration_unit() -> ConfigurationUnitPtr;
} // namespace state

#endif // CROW_CROW_STATE_CONFIGURATION_UNIT_HPP
