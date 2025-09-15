#include "crow_parser.hpp"

// STL Includes:
#include <exception>
#include <string>

// Absolute Includes:
#include "crow/ast/node/include_nodes.hpp"
#include "crow/debug/trace.hpp"

// Macros:
#define CONTEXT_GUARD(t_context)                   \
  context::ContextGuard CONCAT(trace, __COUNTER__) \
  {                                                \
    context::Context::t_context, m_store           \
  }

namespace parser::crow {
// Using statements:
NODE_USING_ALL_NAMESPACES()

// Protected Methods:
auto CrowParser::context_check(const Context t_context) -> void
{
  const auto enabled{m_store.get(t_context)};

  if(!enabled) {
    throw_syntax_error("Keyword used outside of proper context.");
  }
}

// Public Methods:
CrowParser::CrowParser(TokenStream t_token_stream)
  : PrattParser{std::move(t_token_stream)}, m_store{}
{}

auto CrowParser::newline_opt() -> void
{
  DBG_TRACE_FN(VERBOSE);

  while(!eos() && next_if(TokenType::NEWLINE)) {
    DBG_TRACE_PRINT(INFO, "Found 'NEWLINE'");
  }
}

auto CrowParser::terminator() -> void
{
  DBG_TRACE_FN(VERBOSE);

  const auto is_terminator{[this] {
    return next_if(TokenType::SEMICOLON, TokenType::NEWLINE);
  }};

  if(!is_terminator()) {
    throw_syntax_error("Expected at least one 'TERMINATOR'");
  }

  while(!eos()) {
    if(is_terminator()) {
      DBG_TRACE_PRINT(INFO, "Found 'TERMINATOR'");
    } else {
      break;
    }
  }
}

auto CrowParser::literal_list() -> NodeListPtr
{
  DBG_TRACE_FN(VERBOSE);
  auto nodes{make_node<List>()};

  auto pos{get_position()};
  if(auto first_ptr{literal()}; first_ptr) {
    nodes->push_back(std::move(first_ptr));

    while(!eos()) {
      if(next_if(TokenType::COMMA)) {
        auto ptr{literal()};
        if(!ptr) {
          throw_syntax_error("Expected another literal!");
        }

        nodes->push_back(std::move(ptr));
      } else {
        break;
      }
    }
  }

  if(nodes->empty()) {
    throw_syntax_error("Expected a list of literals");
  }

  return nodes;
}

auto CrowParser::expr_opt() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);

  return expr();
}

// FIXME: This is "temporary method", improve later.
auto CrowParser::init_expr(const TokenType t_type) -> NodePtr
{
  using namespace token;

  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  const auto pos{get_position()};
  if(next_if(t_type)) {
    PARSER_FOUND(t_type);

    const auto id{expect(TokenType::IDENTIFIER)};
    std::string type;
    NodePtr expr_ptr;

    const auto get_expr{[&]() {
      newline_opt();
      expr_ptr = expr();
    }};

    if(next_if(TokenType::COLON)) {
      type = expect(TokenType::IDENTIFIER).str();

      if(next_if(TokenType::ASSIGNMENT)) {
        get_expr();
      } else if(t_type == TokenType::LET) {
        throw_syntax_error("Variables declared with Let must be initialized.");
      }
    } else {
      expect(TokenType::ASSIGNMENT);
      get_expr();
    }

    // TODO: Have this selection be done more elegantly.
    if(t_type == TokenType::VAR) {
      node = make_node<Var>(pos, id.str(), type, std::move(expr_ptr));
    } else if(t_type == TokenType::LET) {
      node = make_node<Let>(pos, id.str(), type, std::move(expr_ptr));
    } else {
      // TODO: Error
    }
  }

  return node;
}

auto CrowParser::let_expr() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);

  return init_expr(TokenType::LET);
}

auto CrowParser::var_expr() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);

  return init_expr(TokenType::VAR);
}

auto CrowParser::decl_expr() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(auto ptr{var_expr()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{let_expr()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

auto CrowParser::eval_expr() -> EvalPair
{
  DBG_TRACE_FN(VERBOSE);
  EvalPair pair;

  if(auto ptr{decl_expr()}; ptr) {
    expect(TokenType::SEMICOLON);

    pair = {std::move(ptr), expr()};
  } else if(auto ptr{expr()}; ptr) {
    pair.second = std::move(ptr);
  }

  return pair;
}

auto CrowParser::expr_statement() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(auto ptr{expr()}; ptr) {
    terminator();
    node = std::move(ptr);
  }

  return node;
}

auto CrowParser::expr_list() -> NodeListPtr
{
  DBG_TRACE_FN(VERBOSE);
  auto nodes{expr_list_opt()};

  if(nodes->empty()) {
    throw_syntax_error("Expected a list of expressions");
  }

  return nodes;
}

auto CrowParser::expr_list_opt() -> NodeListPtr
{
  DBG_TRACE_FN(VERBOSE);
  auto nodes{make_node<List>()};

  if(auto ptr{expr()}; ptr) {
    DBG_TRACE_PRINT(INFO, "Found 'EXPR");

    nodes->push_back(std::move(ptr));
  }

  while(!eos()) {
    if(next_if(TokenType::COMMA)) {
      newline_opt();
      if(auto ptr{expr()}; ptr) {
        DBG_TRACE_PRINT(INFO, "Found ',' 'EXPR'");

        nodes->push_back(std::move(ptr));
      } else {
        throw_syntax_error("Expected another expression after ','");
      }
    } else {
      break;
    }
  }

  return nodes;
}

// Result statement:
auto CrowParser::assignment() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(auto lhs{lvalue()}; lhs) {
    const auto pos{get_position()};
    const auto lambda{[&](const AssignmentOp t_op) {
      newline_opt();
      if(auto rhs{expr()}; rhs) {
        node = make_node<Assignment>(pos, t_op, std::move(lhs), std::move(rhs));
      }
    }};

    if(next_if(TokenType::MUL_ASSIGN)) {
      PARSER_FOUND(TokenType::MUL_ASSIGN);
      lambda(AssignmentOp::MULTIPLY);

    } else if(next_if(TokenType::DIV_ASSIGN)) {
      PARSER_FOUND(TokenType::DIV_ASSIGN);
      lambda(AssignmentOp::DIVIDE);

    } else if(next_if(TokenType::MOD_ASSIGN)) {
      PARSER_FOUND(TokenType::MOD_ASSIGN);
      lambda(AssignmentOp::MODULO);

    } else if(next_if(TokenType::ADD_ASSIGN)) {
      PARSER_FOUND(TokenType::ADD_ASSIGN);
      lambda(AssignmentOp::ADD);

    } else if(next_if(TokenType::SUB_ASSIGN)) {
      PARSER_FOUND(TokenType::SUB_ASSIGN);
      lambda(AssignmentOp::SUBTRACT);

    } else if(next_if(TokenType::ASSIGNMENT)) {
      PARSER_FOUND(TokenType::ASSIGNMENT);
      lambda(AssignmentOp::REGULAR);

      // Postcrement part of the method.
    } else if(next_if(TokenType::INCREMENT)) {
      PARSER_FOUND(TokenType::INCREMENT);
      node = make_node<Increment>(std::move(lhs));
    } else if(next_if(TokenType::DECREMENT)) {
      PARSER_FOUND(TokenType::DECREMENT);
      node = make_node<Decrement>(std::move(lhs));
    }
  }

  return node;
}

auto CrowParser::result_statement() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(auto ptr{function_call()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{decl_expr()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{assignment()}; ptr) {
    node = std::move(ptr);
  }

  // Terminate result statement.
  if(node) {
    terminator();
  }

  return node;
}

auto CrowParser::jump_statement() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(check(TokenType::CONTINUE)) {
    context_check(Context::LOOP);
    next();

    terminator();
    node = make_node<Continue>();
  } else if(check(TokenType::BREAK)) {
    context_check(Context::LOOP);
    next();

    terminator();
    node = make_node<Break>();
  } else if(next_if(TokenType::DEFER)) {
    auto body_ptr{make_node<List>()};
    if(auto ptr{body()}; ptr) {
      body_ptr = std::move(ptr);
    } else if(auto ptr{expr_statement()}; ptr) {
      body_ptr->push_back(std::move(ptr));
    }

    node = make_node<Defer>(std::move(body_ptr));
  } else if(next_if(TokenType::RETURN)) {
    auto expr_ptr{expr_opt()};
    terminator();

    node = make_node<Return>(std::move(expr_ptr));
  }

  return node;
}

// FIXME: Currently i++ (postcrement) is not a expression.
// So we have to change the grammar to allow result_statements or similar.
// Potentially we could add a new grammar rule special for loops.
auto CrowParser::loop_statement() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  const auto pos{get_position()};
  if(next_if(TokenType::LOOP)) {
    auto [init, cond] = eval_expr();

    NodePtr expr_ptr;
    if(next_if(TokenType::SEMICOLON)) {
      expr_ptr = assignment();
    }

    // We are in the loop context now.
    CONTEXT_GUARD(LOOP);
    auto body_ptr{body()};
    node = make_node<Loop>(pos, std::move(init), std::move(cond),
                           std::move(expr_ptr), std::move(body_ptr));
  }

  return node;
}

auto CrowParser::branch_statement(const TokenType t_type) -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  const auto pos{get_position()};
  if(next_if(t_type)) {
    auto [init, cond] = eval_expr();
    if(!cond) {
      throw_syntax_error("Expected a conditional");
    }

    auto then_ptr{body()};

    NodeListPtr alt_ptr{};
    if(next_if(TokenType::ELSE)) {
      alt_ptr = body();
    } else if(auto ptr{branch_statement(TokenType::ELIF)}; ptr) {
      // Elifs are structured in the AST as just an if in an else branch
      alt_ptr = make_node<List>();
      alt_ptr->push_back(std::move(ptr));
    }

    node = make_node<If>(pos, std::move(init), std::move(cond),
                         std::move(then_ptr), std::move(alt_ptr));
  }

  return node;
}

auto CrowParser::if_statement() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  return branch_statement(TokenType::IF);
}

auto CrowParser::elif_statement() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);

  return branch_statement(TokenType::ELIF);
}

// TODO: Error out on literals in the body those should be illegal.
auto CrowParser::statement() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(auto ptr{decl_expr()}; ptr) {
    terminator();
    node = std::move(ptr);
  } else if(auto ptr{result_statement()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{if_statement()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{loop_statement()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{jump_statement()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{body()}; ptr) {
    node = std::move(ptr);
    // TODO: Detect expressions which have no side effects and throw.
    // } else if() {
    // throw_syntax_error();
  }

  return node;
}

auto CrowParser::statement_list() -> NodeListPtr
{
  DBG_TRACE_FN(VERBOSE);

  return list_of([this] {
    NodePtr stmnt{statement()};

    if(stmnt) {
      newline_opt();
    }

    return stmnt;
  });
}

// Body:
/*!
 * The @ref body() should never be optional.
 * Or else we will consume newlines unintentionally.
 */
auto CrowParser::body() -> NodeListPtr
{
  DBG_TRACE_FN(VERBOSE);
  NodeListPtr nodes{};

  // After a list of newlines an accolade most occur
  if(after_newlines(TokenType::ACCOLADE_OPEN)) {
    expect(TokenType::ACCOLADE_OPEN);

    newline_opt();
    if(auto ptr{statement_list()}; ptr) {
      nodes = std::move(ptr);
    }

    expect(TokenType::ACCOLADE_CLOSE);
  }

  return nodes;
}

// Struct:
auto CrowParser::member_decl() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  const auto token{get_token()};
  if(next_if(TokenType::IDENTIFIER)) {
    const auto id{token.str()};
    expect(TokenType::COLON);

    const auto type{expect(TokenType::IDENTIFIER).str()};
    terminator();

    node = make_node<MemberDecl>(id, type);
  }

  return node;
}

auto CrowParser::member_decl_list() -> NodeListPtr
{
  DBG_TRACE_FN(VERBOSE);

  return list_of([this] {
    return member_decl();
  });
}

auto CrowParser::struct_def() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(next_if(TokenType::STRUCT)) {
    PARSER_FOUND(TokenType::STRUCT);

    const auto id{expect(TokenType::IDENTIFIER).str()};
    newline_opt();

    auto members{accolades([this] {
      newline_opt();

      return member_decl_list();
    })};

    node = make_node<Struct>(id, std::move(members));
  }

  return node;
}

auto CrowParser::type_def() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(auto ptr{struct_def()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

// Function:
auto CrowParser::param_list() -> NodeListPtr
{
  DBG_TRACE_FN(VERBOSE);
  auto nodes{param_list_opt()};

  if(nodes->empty()) {
    throw_syntax_error("Expected list of parameters");
  }

  return nodes;
}

auto CrowParser::param_list_opt() -> NodeListPtr
{
  DBG_TRACE_FN(VERBOSE);
  auto nodes{make_node<List>()};

  auto pos{get_position()};
  if(check(TokenType::IDENTIFIER)) {
    PARSER_FOUND(TokenType::IDENTIFIER);

    const auto id{expect(TokenType::IDENTIFIER).str()};
    expect(TokenType::COLON);
    const auto type{expect(TokenType::IDENTIFIER).str()};

    nodes->push_back(make_node<Parameter>(pos, id, type));

    while(!eos()) {
      if(next_if(TokenType::COMMA)) {
        pos = get_position();
        const auto id{expect(TokenType::IDENTIFIER).str()};
        PARSER_FOUND(TokenType::COMMA, "'IDENTIFIER'");

        expect(TokenType::COLON);
        const auto type{expect(TokenType::IDENTIFIER).str()};

        nodes->push_back(make_node<Parameter>(pos, id, type));
      } else {
        break;
      }
    }
  }

  return nodes;
}

// TODO: Create a StrOpt type
auto CrowParser::return_type() -> std::string
{
  DBG_TRACE_FN(VERBOSE);
  const auto type{return_type_opt()};

  if(type.empty()) {
    throw_syntax_error("Expected a return type!");
  }

  return type;
}

auto CrowParser::return_type_opt() -> std::string
{
  DBG_TRACE_FN(VERBOSE);
  std::string type{};

  if(after_newlines(TokenType::ARROW)) {
    expect(TokenType::ARROW);
    type = expect(TokenType::IDENTIFIER).str();
  }

  return type;
}

auto CrowParser::lambda() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(next_if(TokenType::FUNCTION)) {
    auto params{parens([this] {
      return this->param_list_opt();
    })};
  }

  return node;
}

auto CrowParser::function() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(next_if(TokenType::FUNCTION)) {
    PARSER_FOUND(TokenType::FUNCTION);

    const auto tt_id{expect(TokenType::IDENTIFIER)};
    const auto id{tt_id.str()};

    expect(TokenType::PAREN_OPEN);

    // NodeListPtr params;
    NodeListPtr params{};
    if(next_if(TokenType::SELF)) {
      // Dealing with a method:
      PARSER_FOUND(TokenType::SELF);
      expect(TokenType::COLON);
      auto receiver_type{expect(TokenType::IDENTIFIER).str()};

      if(next_if(TokenType::COMMA)) {
        // Get the rest of the parameters.
        params = param_list_opt();
      }
      expect(TokenType::PAREN_CLOSE);

      const auto return_type{return_type_opt()};
      auto body_ptr{body()};
      if(!body_ptr) {
        throw_syntax_error("Expected a method body");
      }

      node = make_node<Method>(id, receiver_type, std::move(params),
                               return_type, std::move(body_ptr));
    } else {
      // Dealing with a function:
      params = param_list_opt();
      expect(TokenType::PAREN_CLOSE);

      const auto return_type{return_type_opt()};
      auto body_ptr{body()};
      if(!body_ptr) {
        throw_syntax_error("Expected a function body");
      }

      node = make_node<Function>(id, std::move(params), return_type,
                                 std::move(body_ptr));
    }
  }

  return node;
}

auto CrowParser::attribute_item() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(auto ptr{attribute()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{declare()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{decl_expr()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{function()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

auto CrowParser::attribute_item_list() -> NodeListPtr
{
  DBG_TRACE_FN(VERBOSE);

  return list_of([this] {
    NodePtr attr_item{attribute_item()};

    if(attr_item) {
      newline_opt();
    }

    return attr_item;
  });
}

auto CrowParser::attribute_body() -> NodeListPtr
{
  DBG_TRACE_FN(VERBOSE);
  auto nodes{make_node<List>()};

  if(next_if(TokenType::ACCOLADE_OPEN)) {
    PARSER_FOUND(TokenType::ACCOLADE_OPEN);
    newline_opt();
    nodes = attribute_item_list();
    newline_opt();
    expect(TokenType::ACCOLADE_CLOSE);
  } else if(auto ptr{attribute_item()}; ptr) {
    nodes->push_back(std::move(ptr));
    newline_opt();
  } else {
    throw_syntax_error("Expected an attribute item or body.");
  }

  return nodes;
}

auto CrowParser::attribute() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(next_if(TokenType::ATTRIBUTE_OPEN)) {
    PARSER_FOUND(TokenType::ATTRIBUTE_OPEN);
    const auto id{expect(TokenType::IDENTIFIER).str()};
    NodeListPtr params_ptr{};
    NodeListPtr body_ptr{make_node<List>()};

    // Get any potential parameters (can be nullptr or zero).
    if(next_if(TokenType::PAREN_OPEN)) {
      params_ptr = literal_list();

      expect(TokenType::PAREN_CLOSE);
    }
    expect(TokenType::ATTRIBUTE_CLOSE);

    // Get the item or body.
    newline_opt();
    body_ptr = attribute_body();

    node = make_node<Attribute>(id, std::move(params_ptr), std::move(body_ptr));
  }

  return node;
}

auto CrowParser::declare() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(next_if(TokenType::DECLARE)) {
    PARSER_FOUND(TokenType::DECLARE);
    std::string id{};
    std::string type{};
    std::string ret_type{};

    if(next_if(TokenType::FUNCTION)) {
      id = expect(TokenType::IDENTIFIER).str();

      auto params{parens([this] {
        return this->param_list_opt();
      })};

      ret_type = return_type();

      node = make_node<FunctionDecl>(id, std::move(params), ret_type);
    } else if(next_if(TokenType::LET)) {
      id = expect(TokenType::IDENTIFIER).str();
      expect(TokenType::COLON);
      type = expect(TokenType::IDENTIFIER).str();

      node = make_node<LetDecl>(id, type);
    } else if(next_if(TokenType::VAR)) {
      id = expect(TokenType::IDENTIFIER).str();
      expect(TokenType::COLON);
      type = expect(TokenType::IDENTIFIER).str();

      node = make_node<VarDecl>(id, type);
    } else {
      // TODO: Error handle.
    }
  }

  return node;
}

auto CrowParser::import_expr(Import& t_import) -> bool
{
  DBG_TRACE_FN(VERBOSE);
  bool is_import_expr{true};

  const auto token{get_token()};
  if(next_if(TokenType::STRING)) {
    auto str{token.str()};
    DBG_TRACE_PRINT(INFO, "Found: ", std::quoted(str));

    t_import.add_import(std::move(str));
  } else if(next_if(TokenType::IDENTIFIER)) {
    auto id{token.str()};

    expect(TokenType::ASSIGNMENT);
    auto str{expect(TokenType::STRING).str()};

    DBG_TRACE_PRINT(INFO, "Found alias: ", id, " = ", std::quoted(str));

    t_import.add_import({str, id});
  } else {
    is_import_expr = false;
  }

  return is_import_expr;
}

auto CrowParser::import_list(Import& t_import) -> void
{
  DBG_TRACE_FN(VERBOSE);

  if(!import_expr(t_import)) {
    throw_syntax_error("Expected at least one import expression!");
  }

  while(!eos()) {
    if(check(TokenType::SEMICOLON)) {
      terminator();

      if(!import_expr(t_import)) {
        throw_syntax_error("Expected another import expression!");
      }
    } else if(next_if(TokenType::NEWLINE)) {
      newline_opt();

      if(!import_expr(t_import)) {
        break;
      }
    } else {
      break;
    }
  }
}

auto CrowParser::import_() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(next_if(TokenType::IMPORT)) {
    PARSER_FOUND(TokenType::IMPORT);

    auto import_ptr{make_node<Import>()};
    if(check(TokenType::STRING)) {
      PARSER_FOUND(TokenType::STRING);
      const auto id{get_token()};
      next();

      import_ptr->add_import(id.str());
    } else if(next_if(TokenType::PAREN_OPEN)) {
      newline_opt();
      import_list(*import_ptr);
      expect(TokenType::PAREN_CLOSE);
    } else {
      throw_syntax_error("Expected string or an import list");
    }

    node = std::move(import_ptr);
  }

  return node;
}

auto CrowParser::module_decl() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(next_if(TokenType::MODULE)) {
    PARSER_FOUND(TokenType::MODULE);
    const auto id{expect(TokenType::IDENTIFIER)};

    node = make_node<ModuleDecl>(id.str());
  }

  return node;
}

auto CrowParser::item() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(auto ptr{import_()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{declare()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{attribute()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{type_def()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{decl_expr()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{function()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

// Item list exists out of an item followed by a terminator
// Till there are are no more items
auto CrowParser::item_list() -> NodeListPtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  // Check for the
  if(auto ptr{module_decl()}; ptr) {
    node = std::move(ptr);
  } else {
    throw_syntax_error("First statement in crowlang should be a module name.");
  }

  // Parsing of item_list.
  const auto parse_lambda{[this] -> NodePtr {
    // Remove newlines before item.
    newline_opt();
    if(eos()) {
      return nullptr;
    }

    return item();
  }};

  // Get the item list.
  auto list{list_of(parse_lambda)};
  if(node) {
    // Prepend the module declaration.
    list->push_front(std::move(node));
  }

  return list;
}

// This is the grammars root node.
auto CrowParser::program() -> NodeListPtr
{
  DBG_TRACE_FN(VERBOSE);

  return item_list();
}

auto CrowParser::parse() -> NodePtr
{
  const auto ast{program()};

  // TODO: Check if we are at EOS.
  // If we are not at EOS, then we didnt parse everything.
  // Which is a parsing error or syntax error.
  // As the entirety of the token stream should be parsed and accounted for.

  return ast;
}
} // namespace parser::crow
