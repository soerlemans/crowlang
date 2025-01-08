#ifndef CROW_CROW_SEMANTIC_TYPE_PROMOTER_HPP
#define CROW_CROW_SEMANTIC_TYPE_PROMOTER_HPP

// STL Includes:
#include <array>

// Absolute Includes:
#include "crow/ast/node/node_traits/typing/types.hpp"

/*!
 * @file
 *
 * Contains the classes and methods dedicated to type promotion.
 */

namespace semantic {
// Using statements:
using ast::node::node_traits::typing::NativeType;
using ast::node::node_traits::typing::NativeTypeOpt;

// Aliases:
//! Type for keeping track of the promotion ladder.
using TypeLadder = std::unordered_map<NativeType, int>;

// Classes:
class TypePromoter {
  private:
  TypeLadder m_float;
  TypeLadder m_int;
  TypeLadder m_uint;

  protected:
  auto get_priority(const TypeLadder& t_ladder, NativeType t_type) const
    -> TypeLadder::mapped_type;

  public:
  TypePromoter();

  //! Handles type promotion for unary cases.
  auto promote_bool(NativeType t_lhs) const -> NativeTypeOpt;

  // Type promotion for binary cases:
  auto promote_float(NativeType t_lhs, NativeType t_rhs,
                     bool enforce_lhs = false) const -> NativeTypeOpt;
  auto promote_int(NativeType t_lhs, NativeType t_rhs,
                   bool enforce_lhs = false) const -> NativeTypeOpt;
  auto promote_uint(NativeType t_lhs, NativeType t_rhs,
                    bool enforce_lhs = false) const -> NativeTypeOpt;

  /*!
   * Handles type promotion between two different types.
   *
   * @param[in] t_lhs Left hand side to check for promotion.
   * @param[in] t_rhs Right hand side to check for promotion.
   * @param[in] cast When true promotes rhs to the type of lhs.
   *
   * @return Optional containing a @ref NativeType if promoted.
   */
  auto promote(NativeType t_lhs, NativeType t_rhs,
               bool enforce_lhs = false) const -> NativeTypeOpt;

  virtual ~TypePromoter() = default;
};
} // namespace semantic

#endif // CROW_CROW_SEMANTIC_TYPE_PROMOTER_HPP
