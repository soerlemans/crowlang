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
 * In the @ref ClirBuilder.
 * Here we handle all the boilerplate operations for constructing the CLIR.
 */
class ModuleFactory {
  private:
  ModulePtr m_module;

  // We need to increment these to prevent collisions.
  u64 m_var_id;
  u64 m_instr_id;

  public:
  ModuleFactory();

  // Instruction operations:
  [[nodiscard("Must use created instruction.")]]
  auto create_instruction(Opcode t_opcode) -> Instruction;
  auto add_instruction(Opcode t_opcode) -> Instruction&;

  /*!
   * We usually add a jump statement in retrospect between two blocks.
   * So we need to supply everything manually to fix instruction numbering.
	 * (in some cases).
	 */
  auto insert_jump(Instruction t_instr, BasicBlock& t_block,
                   BasicBlock& t_target) -> void;
  auto insert_jump(BasicBlock& t_block, BasicBlock& t_target) -> void;

  auto last_instruction() -> Instruction&;

  // Block operations:
  auto add_block(std::string_view t_label) -> BasicBlock&;

  /*!
   * @return nullptr if there is no basicblock associated with the given label.
   */
  auto find_block(std::string_view t_label) -> BasicBlock*;
  auto last_block() -> BasicBlock&;

  // Function operations:
  auto add_function(Function&& t_fn) -> void;
  auto last_function() -> Function&;

  // Module operations:
  auto set_module_name(std::string_view t_name) -> void;

  auto get_module() -> ModulePtr;

  virtual ~ModuleFactory() = default;
};
} // namespace clir::clir_builder

#endif // CROW_CROW_CLIR_CLIR_BUILDER_MODULE_FACTORY_HPP
