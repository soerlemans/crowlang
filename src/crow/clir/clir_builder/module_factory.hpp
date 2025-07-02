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

  // We need to increment these to prevent collisions.
  u64 m_var_id;
  u64 m_instr_id;

  public:
  ModuleFactory();

  auto create_ir(Opcode t_opcode) -> void;

  auto create_bblock(std::string_view t_label) -> BasicBlock&;
  //! Return nullptr if there is no basicblock associated with the given label.
  auto get_bblock_ref(std::string_view t_label) -> BasicBlock*;

  // TODO: Account for if there is no basic block (maybe throw).
  auto last_bblock() -> BasicBlock&;

  auto create_function(Function&& t_fn) -> void;

  // TODO: Account for if there is no function yet (maybe throw).
  auto last_function() -> Function&;

  auto set_module_name(std::string_view t_name) -> void;

  auto get_module() -> ModulePtr;

  virtual ~ModuleFactory() = default;
};
} // namespace clir::clir_builder

#endif // CROW_CROW_CLIR_CLIR_BUILDER_MODULE_FACTORY_HPP
