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
class ClirModuleFactory {
  private:
  ModulePtr m_module;

  // We need two separate environments to prevent IR temporaries from clashing.
  // Semantic pass should prevent any variables and functions from conflicting.
  SsaVarEnvState m_var_env;
  FunctionEnvState m_fn_env;

  // We need to increment these to prevent collisions.
  u64 m_var_id;
  u64 m_instr_id;

  public:
  ClirModuleFactory();

  // Env operations:
  auto push_env() -> void;
  auto pop_env() -> void;
  auto clear_env() -> void;

  // SsaVar operations:
  auto create_var(types::core::TypeVariant t_type) -> SsaVarPtr;
  auto add_result_var(types::core::TypeVariant t_type) -> SsaVarPtr;

  /*!
   * Every instruction has a result.
   * Can be a nullptr (indicating the operation did no result).
   */
  auto last_var() -> SsaVarPtr;
  auto require_last_var() -> SsaVarPtr;

  // Instruction operations:
  [[nodiscard("Must use created instruction.")]]
  auto create_instruction(Opcode t_opcode) -> Instruction;
  auto add_instruction(Opcode t_opcode) -> Instruction&;
  auto add_comment(std::string t_comment) -> void;

  //! Add a literal which also creates the proper instruction for it.
  auto add_literal(NativeType t_type, LiteralValue t_value) -> void;

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

  virtual ~ClirModuleFactory() = default;
};
} // namespace clir::clir_builder

#endif // CROW_CROW_CLIR_CLIR_BUILDER_CLIR_MODULE_FACTORY_HPP
