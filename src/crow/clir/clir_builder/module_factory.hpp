#ifndef CROW_CROW_CLIR_CLIR_BUILDER_MODULE_FACTORY_HPP
#define CROW_CROW_CLIR_CLIR_BUILDER_MODULE_FACTORY_HPP

// STL Includes:
#include <memory>

// Absolute Includes:
#include "crow/clir/clir.hpp"

namespace clir::clir_builder {
// Forward Declarations:
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

  u64 m_value_id;
  u64 m_instr_id;

  public:
  ModuleFactory();

  auto create_ir(Opcode t_opcode) -> void;

  auto create_bblock(std::string_view t_label) -> void;
  auto get_bblock(std::string_view t_label) -> BasicBlock&;
  auto last_bblock() -> BasicBlock&;

  auto create_function(Function&& t_fn) -> void;
  auto last_function() -> Function&;

  auto set_module_name(std::string_view t_name) -> void;

  auto get_module() -> ModulePtr;

  virtual ~ModuleFactory() = default;
};
} // namespace clir::clir_builder

#endif // CROW_CROW_CLIR_CLIR_BUILDER_MODULE_FACTORY_HPP
