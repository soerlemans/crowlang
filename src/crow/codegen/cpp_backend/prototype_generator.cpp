#include "prototype_generator.hpp"

// STL Includes:
#include <iostream>

// Absolute Includes:
#include "crow/ast/node/include_nodes.hpp"
#include "crow/exception/error.hpp"

namespace codegen::cpp_backend {
// Using Statements:
using namespace ast::visitor;

NODE_USING_ALL_NAMESPACES()

// Methods:
// FIXME: I was lazy and copied this from @ref CppBackend.
// I should fix this by having some kind of StrNodeVisitor class or something.
auto PrototypeGenerator::resolve(NodePtr t_ptr) -> std::string
{
  using exception::error;

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
// TODO: Resolve the parameter type to a valid type.
auto PrototypeGenerator::visit([[maybe_unused]] Parameter* t_param) -> Any
{
  return {};
}

auto PrototypeGenerator::visit(Function* t_fn) -> Any
{
  const auto identifier{t_fn->identifier()};

  // TODO: Some day resolve the TypeVariant, for now every method returns int.
  const auto ret_type{"int"};

  std::stringstream ss;

  // TODO: Process parameters.

  // clang-format off
  ss << std::format("auto {}() -> {};\n", identifier, ret_type);
  // clang-format on

  return ss.str();
}

// Typing:
auto PrototypeGenerator::visit([[maybe_unused]] Struct* t_struct) -> Any
{

  return {};
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
