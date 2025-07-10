#include "clir_module_factory.hpp"

// STL Includes:
#include <memory>

namespace clir::clir_builder {
ClirModuleFactory::ClirModuleFactory()
  : m_module{std::make_shared<Module>()}, m_var_id{0}, m_instr_id{0}
{}

auto ClirModuleFactory::create_var(types::core::TypeVariant t_type) -> SsaVarPtr
{
  auto ptr{std::make_shared<SsaVar>(m_var_id, t_type)};

  m_var_id++;

  return ptr;
}

auto ClirModuleFactory::last_ssa_var() -> SsaVarPtr
{
  auto& instr{last_instruction()};

  return instr.m_result;
}

auto ClirModuleFactory::require_last_ssa_var() -> SsaVarPtr
{
  auto var{last_ssa_var()};
  if(!var) {
    // TODO: Throw stacktraced exception.
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

auto ClirModuleFactory::add_literal(NativeType t_type, LiteralValue t_value)
  -> void
{
  Opcode opcode{};

  // Translate native type to literal opcode.
  // TODO: Create a separate helper function for this.
  switch(t_type) {
    case NativeType::BOOL:
      opcode = Opcode::CONST_BOOL;
      break;

    default:
      throw std::runtime_error("ClirModuleFactory::add_literal(): Given native "
                               "type is unsupported.");
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
                                    BasicBlock& t_target) -> void
{
  auto& instructions{t_block.m_instructions};

  // Create label operand.
  Label label{&t_target};

  // Add label to operands.
  auto& operands{t_instr.m_operands};
  operands.push_back({label});

  // Push back instruction to source block.
  instructions.push_back(t_instr);
}

auto ClirModuleFactory::insert_jump(BasicBlock& t_block, BasicBlock& t_target)
  -> void
{
  auto jmp_instr{create_instruction(Opcode::JUMP)};

  insert_jump(jmp_instr, t_block, t_target);
}

auto ClirModuleFactory::last_instruction() -> Instruction&
{
  auto& block{last_block()};
  auto& instructions{block.m_instructions};

  if(instructions.empty()) {
    throw std::runtime_error{
      "There are no instructions in the current basic block"
      ", cant retrieve last one."};
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
    throw std::runtime_error{"There are no basic blocks in current function"
                             ", cant retrieve last one."};
  }

  return fn.m_blocks.back();
}

auto ClirModuleFactory::add_function(Function&& t_fn) -> void
{
  auto& functions{m_module->m_functions};

  functions.push_back(t_fn);
}

auto ClirModuleFactory::last_function() -> Function&
{
  auto& functions{m_module->m_functions};

  if(functions.empty()) {
    throw std::runtime_error{"There are no functions in current CLIR module, "
                             "can retrieve last one."};
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
