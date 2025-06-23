#include "module_factory.hpp"

// STL Includes:
#include <memory>

namespace clir::clir_builder {
ModuleFactory::ModuleFactory(): m_module{std::make_shared<Module>()}
{}

auto ModuleFactory::create_bblock(const std::string_view t_label) -> void
{
  auto& fn{current_function()};
  auto& blocks{fn.m_blocks};

  BasicBlock bblock{};

  bblock.m_label = t_label;

  blocks.push_back(std::move(bblock));
}

auto ModuleFactory::current_bblock() -> BasicBlock&
{
  auto& fn{current_function()};

  return fn.m_blocks.back();
}

auto ModuleFactory::create_function(Function&& t_fn) -> void
{
  auto& functions{m_module->m_functions};

  functions.push_back(std::move(t_fn));
}

auto ModuleFactory::current_function() -> Function&
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
