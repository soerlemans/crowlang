#include "module_factory.hpp"

// STL Includes:
#include <memory>

namespace clir::clir_builder {
ModuleFactory::ModuleFactory()
  : m_module{std::make_shared<Module>()}, m_value_id{0}, m_instr_id{0}
{}

auto ModuleFactory::create_ir(const Opcode t_opcode) -> void
{
  auto& block{last_bblock()};
  auto& instructions{block.m_instructions};

  Instruction instr{};

  instr.m_id = m_instr_id;
  instr.m_opcode = t_opcode;

  m_instr_id++;

  instructions.push_back(std::move(instr));
}

auto ModuleFactory::create_bblock(const std::string_view t_label) -> void
{
  auto& fn{last_function()};
  auto& blocks{fn.m_blocks};

  BasicBlock bblock{};

  bblock.m_label = t_label;

  blocks.push_back(std::move(bblock));
}

auto ModuleFactory::get_bblock(const std::string_view t_label) -> BasicBlock&
{
  // TODO: Implement
  return last_bblock();
}

auto ModuleFactory::last_bblock() -> BasicBlock&
{
  auto& fn{last_function()};

  return fn.m_blocks.back();
}

auto ModuleFactory::create_function(Function&& t_fn) -> void
{
  auto& functions{m_module->m_functions};

  functions.push_back(std::move(t_fn));
}

auto ModuleFactory::last_function() -> Function&
{
  auto& functions{m_module->m_functions};

  // TODO: Error if fucntions.empty() is true?

  return functions.back();
}

auto ModuleFactory::set_module_name(std::string_view t_name) -> void
{
  m_module->m_name = t_name;
}

auto ModuleFactory::get_module() -> ModulePtr
{
  return m_module;
}
} // namespace clir::clir_builder
