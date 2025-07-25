#ifndef CROW_CROW_MIR_MIR_BUILDER_MIR_MODULE_FACTORY_HPP
#define CROW_CROW_MIR_MIR_BUILDER_MIR_MODULE_FACTORY_HPP

// STL Includes:
#include <memory>

// Absolute Includes:
#include "crow/mir/mir.hpp"
#include "crow/mir/mir_builder/mir_env_state.hpp"

namespace mir::mir_builder {
// Forward Declarations:
class MirModuleFactory;

// Aliases:
using MirModuleFactoryPtr = std::unique_ptr<MirModuleFactory>;

using SsaVarEnvState = MirEnvState<SsaVarPtr>;
using FunctionEnvState = MirEnvState<Function*>;

// Classes:
/*!
 * Utility class to aid building a CLIR module.
 * When walking the AST.
 * In the @ref MirBuilder.
 * Here we handle all the boilerplate operations for constructing the CLIR.
 *
 * @note Any method starting with `create_` will create that item.
 * But not add it to the current module the factory is building.
 *
 * @note Any method starting with `add_` will create that item.
 * As well as add itto the last item it can be added to.
 *
 * @note Any method starting with `last_` will retrieve the last item.
 * Of that object that was added to the module.
 */
class MirModuleFactory {
  private:
  ModulePtr m_module;

  // We need two separate environments to prevent IR temporaries from clashing.
  // Semantic pass should prevent any variables and functions from conflicting.
  SsaVarEnvState m_var_env;
  FunctionEnvState m_fn_env;

  // We need to increment these to prevent collisions.
  u64 m_block_id;
  u64 m_instr_id;
  u64 m_var_id;

  public:
  MirModuleFactory();

  // Env operations:
  auto push_env() -> void;
  auto pop_env() -> void;
  auto clear_env() -> void;

  // SsaVar operations:
  [[nodiscard("Must use created ssa var.")]]
  auto create_var(types::core::TypeVariant t_type) -> SsaVarPtr;
  auto add_result_var(types::core::TypeVariant t_type) -> SsaVarPtr;

  /*!
   * Returns the result @ref SsaVarPtr from the last @ref Instruction.
   *
   * @remark Can be a nullptr if last instruction has no result variable.
   */
  auto last_var() -> SsaVarPtr;

  /*!
   * Returns the result @ref SsaVarPtr from the last @ref Instruction.
   *
   * @remark Throws if the last instruction has no result variable.
   */
  auto require_last_var() -> SsaVarPtr;

  // Instruction operations:
  [[nodiscard("Must use created instruction.")]]
  auto create_instruction(Opcode t_opcode) -> Instruction;
  auto add_instruction_to(Opcode t_opcode, BasicBlock& t_block) -> Instruction&;
  auto add_instruction(Opcode t_opcode) -> Instruction&;
  auto add_comment(std::string t_comment) -> void;

  //! Add a literal which also creates the proper instruction for it.
  auto add_literal(NativeType t_type, LiteralValue t_value) -> Instruction&;

  /*!
   * We usually add a jump statement in retrospect between two blocks.
   * So we need to supply everything manually to fix instruction numbering.
   * (in some cases).
   */
  auto insert_jump(Instruction t_instr, BasicBlock& t_block,
                   BasicBlock& t_target) -> Instruction&;
  auto insert_jump(BasicBlock& t_block, BasicBlock& t_target) -> Instruction&;

  /*!
   * Bind a ssa variable to a source variable name.
   */
  auto create_var_binding(std::string_view t_name, SsaVarPtr t_var) -> void;

  /*!
   * Add an init for a variable.
   *
   * @note this binds a source variable name to an ssa var.
   */
  auto add_init(std::string_view t_name, types::core::TypeVariant t_type)
    -> Instruction&;

  /*!
   * Variables need to be referenced to an SSA var.
   * An update statement creates a new statement.
   * Which assigns the old ssa variable, to a new ssa variable.
   * So we can reference the last SSA var.
   */
  auto add_update(std::string_view t_name) -> Instruction&;
  auto add_update(std::string_view t_name, SsaVarPtr t_prev_var)
    -> Instruction&;

  auto last_instruction() -> Instruction&;

  // Block operations:
  [[nodiscard("Must use created block.")]]
  auto create_block(std::string_view t_label) -> BasicBlock;
  auto append_block(const BasicBlock& t_block) -> BasicBlock&;
  auto add_block(std::string_view t_label) -> BasicBlock&;

  /*!
   * @return nullptr if there is no basicblock associated with the given label.
   */
  auto find_block(std::string_view t_label) -> BasicBlock*;
  auto last_block() -> BasicBlock&;

  // Function operations:
  auto add_function(Function&& t_fn) -> void;

  /*!
   * Get a function by name.
   *
   * @note semantic analysis should ensure that a function exists.
   * So if we cant get the function we should throw.
   */
  // auto get_function(std::string_view t_key) -> Function&;

  auto last_function() -> Function&;

  // Module operations:
  auto set_module_name(std::string_view t_name) -> void;

  auto get_module() -> ModulePtr;

  virtual ~MirModuleFactory() = default;
};
} // namespace mir::mir_builder

#endif // CROW_CROW_MIR_MIR_BUILDER_MIR_MODULE_FACTORY_HPP
