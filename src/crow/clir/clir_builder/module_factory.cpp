#include "module_factory.hpp"

// STL Includes:
#include <memory>

namespace clir::clir_builder {
ModuleFactory::ModuleFactory(): m_module{std::make_shared<Module>()}
{}

auto ModuleFactory::create_bblock(std::string_view t_label) -> void
{}

auto ModuleFactory::current_bblock() -> BasicBlock&
{}

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
