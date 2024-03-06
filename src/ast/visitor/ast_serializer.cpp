#include "ast_serializer.hpp"

// Includes:
#include "../../debug/log.hpp"


/*!
 * Defines a @ref AstSerializer method, that will call,
 * @ref AstSerializer::archive() on its argument.
 *
 * @param[in] t_type Type of Node to accept.
 */
#define DEFINE_SERIALIZE_METHOD(t_type)                          \
  auto AstSerializer::visit([[maybe_unused]] t_type* t_ptr)->Any \
  {                                                              \
    archive(*t_ptr);                                             \
                                                                 \
    return {};                                                   \
  }

namespace ast::visitor {
// Using statements:
NODE_USING_ALL_NAMESPACES()

// Methods:
AstSerializer::AstSerializer(): m_archive{std::monostate{}}
{}

// Public: Methods:
// Control:
DEFINE_SERIALIZE_METHOD(If);
DEFINE_SERIALIZE_METHOD(Loop);
DEFINE_SERIALIZE_METHOD(Continue);
DEFINE_SERIALIZE_METHOD(Break);
DEFINE_SERIALIZE_METHOD(Return);

// Function:
DEFINE_SERIALIZE_METHOD(Parameter);
DEFINE_SERIALIZE_METHOD(Function);
DEFINE_SERIALIZE_METHOD(Call);
DEFINE_SERIALIZE_METHOD(ReturnType);

// Lvalue:
DEFINE_SERIALIZE_METHOD(Let);
DEFINE_SERIALIZE_METHOD(Var);
DEFINE_SERIALIZE_METHOD(Variable);

// Operators:
DEFINE_SERIALIZE_METHOD(Arithmetic);
DEFINE_SERIALIZE_METHOD(Assignment);
DEFINE_SERIALIZE_METHOD(Comparison);
DEFINE_SERIALIZE_METHOD(Increment);
DEFINE_SERIALIZE_METHOD(Decrement);
DEFINE_SERIALIZE_METHOD(UnaryPrefix);

// Logical:
DEFINE_SERIALIZE_METHOD(Not);
DEFINE_SERIALIZE_METHOD(And);
DEFINE_SERIALIZE_METHOD(Or);
DEFINE_SERIALIZE_METHOD(Ternary);

// Packaging:
DEFINE_SERIALIZE_METHOD(Import);
DEFINE_SERIALIZE_METHOD(ModuleDecl);

// Rvalue:
DEFINE_SERIALIZE_METHOD(Float);
DEFINE_SERIALIZE_METHOD(Integer);
DEFINE_SERIALIZE_METHOD(String);
DEFINE_SERIALIZE_METHOD(Boolean);

// Typing:
DEFINE_SERIALIZE_METHOD(MethodDecl);
DEFINE_SERIALIZE_METHOD(Interface);
DEFINE_SERIALIZE_METHOD(MemberDecl);
DEFINE_SERIALIZE_METHOD(Struct);
DEFINE_SERIALIZE_METHOD(Impl);
DEFINE_SERIALIZE_METHOD(DotExpr);

// Misc:
DEFINE_SERIALIZE_METHOD(List);
DEFINE_SERIALIZE_METHOD(Nil);

auto AstSerializer::serialize(NodePtr& t_ast, std::ostream& t_os) -> void
{
  m_archive.emplace<XMLOutputArchive>(t_os);

  traverse(t_ast);

  m_archive = std::monostate{};
}

auto AstSerializer::deserialize(NodePtr& t_ast, std::istream& t_is) -> void
{
  m_archive.emplace<XMLInputArchive>(t_is);

	// We do not traverse as this fails on nullptr.
  archive(t_ast);

  m_archive = std::monostate{};
}
} // namespace ast::visitor
