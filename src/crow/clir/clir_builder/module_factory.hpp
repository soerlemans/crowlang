#ifndef CROW_CROW_CLIR_CLIR_BUILDER_MODULE_FACTORY_HPP
#define CROW_CROW_CLIR_CLIR_BUILDER_MODULE_FACTORY_HPP

// STL Includes:
#include <memory>

// Absolute Includes:
#include "crow/clir/clir.hpp"

namespace clir::clir_builder {
class ModuleFactory;

// Aliases:
using ModuleFactoryPtr = std::unique_ptr<ModuleFactory>;

// Classes:
/*!
 * Utility class to aid building a CLIR module.
 * When walking the AST.
 */
class ModuleFactory {
  private:
  ModulePtr m_module;

  public:
  ModuleFactory();

  auto create_bblock(std::string_view t_label) -> void;
  auto current_bblock() -> BasicBlock&;

  auto create_function(Function&& t_fn) -> void;
  auto current_function() -> Function&;

  auto set_module_name(std::string_view t_name) -> void;

  auto get_module() -> ModulePtr;

  virtual ~ModuleFactory() = default;
};
} // namespace clir::clir_builder

#endif // CROW_CROW_CLIR_CLIR_BUILDER_MODULE_FACTORY_HPP
