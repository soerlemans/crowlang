#include "clir_module_factory.hpp"

// STL Includes:
#include <memory>

// Absolute Includes:
#include "lib/stdexcept/stdexcept.hpp"
#include "lib/string_util.hpp"

namespace clir::clir_builder {
ClirModuleFactory::ClirModuleFactory()
  : m_module{std::make_shared<Module>()},
    m_var_env{},
    m_fn_env{},
    m_var_id{0},
    m_instr_id{0}
{}

auto ClirModuleFactory::push_env() -> void
{
  m_var_env.push_env();
  m_fn_env.push_env();
}

auto ClirModuleFactory::pop_env() -> void
{
  m_var_env.pop_env();
  m_fn_env.pop_env();
}

auto ClirModuleFactory::clear_env() -> void
{
  m_var_env.clear();
  m_fn_env.clear();
}

auto ClirModuleFactory::create_var(types::core::TypeVariant t_type) -> SsaVarPtr
{
  auto ptr{std::make_shared<SsaVar>(m_var_id, t_type)};

  const auto key{std::to_string(ptr->m_id)};
  auto [iter, inserted] = m_var_env.insert({key, ptr});
  if(!inserted) {
    using lib::stdexcept::throw_runtime_exception;

    throw_runtime_exception("Can not insert duplicate variable name.");
  }

  m_var_id++;


  return ptr;
}

auto ClirModuleFactory::add_var(types::core::TypeVariant t_type) -> SsaVarPtr
{
  auto ssa_var{create_var(t_type)};
  auto& instr{last_instruction()};

  // Add the variable to the last instruction.
  instr.m_result = ssa_var;

  return ssa_var;
}

auto ClirModuleFactory::last_var() -> SsaVarPtr
{
  auto& instr{last_instruction()};

  return instr.m_result;
}

auto ClirModuleFactory::require_last_var() -> SsaVarPtr
{
  auto var{last_var()};
  if(!var) {
    lib::stdexcept::throw_runtime_exception(
      "Expected last IR instruction to produce an SSA var.");
  }

  return var;
}

auto ClirModuleFactory::create_instruction(const Opcode t_opcode) -> Instruction
{
  // Cookie cutter the creation of an instruction.
  Instruction instr{};

  instr.m_id = m_instr_id;
  instr.m_opcode = t_opcode;
  instr.m_result = nullptr;

  m_instr_id++;

  return instr;
}

auto ClirModuleFactory::add_instruction(const Opcode t_opcode) -> Instruction&
{
  auto& block{last_block()};
  auto& instructions{block.m_instructions};

  auto instr{create_instruction(t_opcode)};
  instructions.push_back(instr);

  return last_instruction();
}

auto ClirModuleFactory::add_comment(std::string t_comment) -> void
{
  auto& instr{last_instruction()};

  lib::strip_whitespace(t_comment);
  lib::trim_whitespace(t_comment);
  t_comment += '.';

  instr.m_comment = t_comment;
}

auto ClirModuleFactory::add_literal(NativeType t_type, LiteralValue t_value)
  -> void
{
  Opcode opcode{};

  // Translate native type to literal opcode.
  // TODO: Create a separate helper function for this.
  switch(t_type) {
    case NativeType::F32:
      opcode = Opcode::CONST_F32;
      break;

    case NativeType::INT:
      opcode = Opcode::CONST_INT;
      break;

    case NativeType::BOOL:
      opcode = Opcode::CONST_BOOL;
      break;

    default:
      lib::stdexcept::throw_invalid_argument(
        "Given native type is unsupported.");
      break;
  }

  // Instruction insertion:
  auto& instr{add_instruction(opcode)};

  // Add the literal as an operand.
  Literal lit{t_type, t_value};
  instr.add_operand(lit);

  auto ssaVar{create_var({t_type})};
  instr.m_result = std::move(ssaVar);
}

auto ClirModuleFactory::insert_jump(Instruction t_instr, BasicBlock& t_block,
                                    BasicBlock& t_target) -> Instruction&
{
  auto& instructions{t_block.m_instructions};

  // Create label operand.
  Label label{&t_target};

  // Add label to operands.
  auto& operands{t_instr.m_operands};
  operands.push_back({label});

  // Push back instruction to source block.
  instructions.push_back(t_instr);

  return instructions.back();
}

auto ClirModuleFactory::insert_jump(BasicBlock& t_block, BasicBlock& t_target)
  -> Instruction&
{
  auto jmp_instr{create_instruction(Opcode::JUMP)};

  return insert_jump(jmp_instr, t_block, t_target);
}

auto ClirModuleFactory::add_init(const std::string_view t_name,
                                 types::core::TypeVariant t_type)
  -> Instruction&
{
  auto& assign_instr{add_instruction(Opcode::INIT)};
  auto result_var{add_var(t_type)};

  // TODO: Check for errors.
  const auto [iter, inserted] =
    m_var_env.insert({std::string{t_name}, result_var});

  if(!inserted) {
    using lib::stdexcept::throw_runtime_exception;

    throw_runtime_exception("Could not insert ", std::quoted(t_name), ".");
  }

  return assign_instr;
}

auto ClirModuleFactory::add_update(const std::string_view t_name)
  -> Instruction&
{
  auto& update_instr{add_instruction(Opcode::UPDATE)};

  auto prev_var{m_var_env.get_value(t_name)};
  update_instr.add_operand(prev_var);

  const auto type{prev_var->m_type};
  auto result_var{add_var(type)};

  // Update with the new result var.
  // For the next variable reference.
  m_var_env.update(t_name, result_var);

  return update_instr;
}

auto ClirModuleFactory::last_instruction() -> Instruction&
{
  auto& block{last_block()};
  auto& instructions{block.m_instructions};

  if(instructions.empty()) {
    using lib::stdexcept::throw_runtime_exception;

    throw_runtime_exception(
      "There are no instructions in the last basic block, cant retrieve "
      "last instruction.");
  }

  return instructions.back();
}

auto ClirModuleFactory::add_block(const std::string_view t_label) -> BasicBlock&
{
  auto& fn{last_function()};
  auto& blocks{fn.m_blocks};

  // Create basic block and set its label.
  BasicBlock block{};
  block.m_label = t_label;

  blocks.push_back(block);

  // Return the just added basic block.
  return last_block();
}

auto ClirModuleFactory::find_block(const std::string_view t_label)
  -> BasicBlock*
{
  BasicBlock* ptr{nullptr};

  auto& fn{last_function()};
  auto& blocks{fn.m_blocks};

  for(BasicBlock& block : blocks) {
    if(block.m_label == t_label) {
      ptr = &block;
      break;
    }
  }

  return ptr;
}

auto ClirModuleFactory::last_block() -> BasicBlock&
{
  auto& fn{last_function()};

  if(fn.m_blocks.empty()) {
    using lib::stdexcept::throw_runtime_exception;

    throw_runtime_exception(
      "There are no basic blocks in the last function, cant retrieve last "
      "basic block.");
  }

  return fn.m_blocks.back();
}

auto ClirModuleFactory::add_function(Function&& t_fn) -> void
{
  auto& functions{m_module->m_functions};

  // TODO: Add environment registration for function.

  functions.push_back(t_fn);
}

auto ClirModuleFactory::last_function() -> Function&
{
  auto& functions{m_module->m_functions};

  if(functions.empty()) {
    using lib::stdexcept::throw_runtime_exception;

    throw_runtime_exception("There are no functions in the CLIR "
                            "module, cant retrieve last function.");
  }

  return functions.back();
}

auto ClirModuleFactory::set_module_name(std::string_view t_name) -> void
{
  m_module->m_name = t_name;
}

auto ClirModuleFactory::get_module() -> ModulePtr
{
  return m_module;
}
} // namespace clir::clir_builder
