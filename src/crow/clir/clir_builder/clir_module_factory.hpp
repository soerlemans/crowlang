#ifndef CROW_CROW_CLIR_CLIR_BUILDER_CLIR_MODULE_FACTORY_HPP
#define CROW_CROW_CLIR_CLIR_BUILDER_CLIR_MODULE_FACTORY_HPP

// STL Includes:
#include <memory>

// Absolute Includes:
#include "crow/clir/clir.hpp"
#include "crow/clir/clir_builder/clir_env_state.hpp"

namespace clir::clir_builder {
// Forward Declarations:
class ClirModuleFactory;

// Aliases:
using ClirModuleFactoryPtr = std::unique_ptr<ClirModuleFactory>;

using SsaVarEnvState = ClirEnvState<SsaVarPtr>;
using FunctionEnvState = ClirEnvState<Function*>;

// Classes:
/*!
 * Utility class to aid building a CLIR module.
 * When walking the AST.
 * In the @ref ClirBuilder.
 * Here we handle all the boilerplate operations for constructing the CLIR.
 */
class ClirModuleFactory {
  private:
  ModulePtr m_module;
  SsaVarEnvState m_ssa_env;
  FunctionEnvState m_fn_env;

  // We need to increment these to prevent collisions.
  u64 m_var_id;
  u64 m_instr_id;

  public:
  ClirModuleFactory();

  // SsaVar operations:
  auto create_var(types::core::TypeVariant t_type) -> SsaVarPtr;

  /*!
   * Every instruction has a result.
   * Can be a nullptr (indicating the operation did no result).
   */
  auto last_ssa_var() -> SsaVarPtr;
  auto require_last_ssa_var() -> SsaVarPtr;

  // Instruction operations:
  [[nodiscard("Must use created instruction.")]]
  auto create_instruction(Opcode t_opcode) -> Instruction;
  auto add_instruction(Opcode t_opcode) -> Instruction&;

  //! Add a literal which also creates the proper instruction for it.
  auto add_literal(NativeType t_type, LiteralValue t_value) -> void;

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

  virtual ~ClirModuleFactory() = default;
};
} // namespace clir::clir_builder

#endif // CROW_CROW_CLIR_CLIR_BUILDER_CLIR_MODULE_FACTORY_HPP
