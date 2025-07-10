#include "prototype_generator.hpp"

// STL Includes:
#include <iostream>

// Absolute Includes:
#include "crow/ast/node/include_nodes.hpp"
#include "crow/diagnostic/error.hpp"

// Local Includes:
#include "type_variant2cpp_type.hpp"

namespace codegen::cpp_backend {
// Using Statements:
using namespace ast::visitor;
using namespace std::literals::string_view_literals;

NODE_USING_ALL_NAMESPACES()

// Methods:
// FIXME: I was lazy and copied this from @ref CppBackend.
// I should fix this by having some kind of StrNodeVisitor class or something.
auto PrototypeGenerator::resolve(NodePtr t_ptr) -> std::string
{
  using diagnostic::error;

  std::stringstream ss;

  if(t_ptr) {
    const auto any{traverse(t_ptr)};

    try {
      ss << std::any_cast<std::string>(any);
    } catch(std::bad_any_cast& exception) {
      error(exception.what());
    }
  }

  return ss.str();
}

// Function:
auto PrototypeGenerator::visit([[maybe_unused]] Parameter* t_param) -> Any
{
  // TODO: Perform type resolution as this will break on u8, i8, u16, etc.
  const auto type{t_param->type()};

  return std::format("{}", type);
}

auto PrototypeGenerator::visit(Function* t_fn) -> Any
{
  const auto identifier{t_fn->identifier()};

  const auto fn_type{t_fn->get_type().function()};
  const auto ret_type{type_variant2cpp_type(fn_type->m_return_type)};

  std::stringstream ss{};

  auto sep{""sv};
  const auto params{t_fn->params()};
  for(const auto& param : *params) {
    ss << sep << resolve(param);

    sep = ", ";
  }

  return std::format("auto {}({}) -> {};\n", identifier, ss.str(), ret_type);
}

auto PrototypeGenerator::visit([[maybe_unused]] ModuleDecl* t_module) -> Any
{
  // TODO: Do something with this.

  return std::string{};
}

// Typing:
auto PrototypeGenerator::visit([[maybe_unused]] Struct* t_struct) -> Any
{

  return std::string{};
}

// Misc:
auto PrototypeGenerator::visit(List* t_list) -> Any
{
  std::stringstream ss;

  for(NodePtr& node : *t_list) {
    ss << resolve(node);
  }

  return ss.str();
}

// Util:
auto PrototypeGenerator::generate(NodePtr t_ast) -> std::string
{
  return resolve(t_ast);
}
} // namespace codegen::cpp_backend
