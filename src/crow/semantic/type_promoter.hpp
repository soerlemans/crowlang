#ifndef CROW_CROW_SEMANTIC_TYPE_PROMOTER_HPP
#define CROW_CROW_SEMANTIC_TYPE_PROMOTER_HPP

// STL Includes:
#include <array>
#include <unordered_map>

// Absolute Includes:
#include "crow/types/core/core.hpp"

/*!
 * @file
 *
 * Contains the classes and methods dedicated to type promotion.
 */

namespace semantic {
// Using statements:
using types::core::NativeType;
using types::core::NativeTypeOpt;

// Aliases:
//! Type for keeping track of the promotion ladder.
using TypeLadder = std::unordered_map<NativeType, int>;

// Enums:
enum class TypeOperandPriority {
  PROMOTE_TO_LHS, //< Check if RHS can be promoted to the LHS.
  ENFORCE_RHS,    //< Enforce the type of RHS no matter what.
  PEAK            //< Enforce highest priority promotion of both operands.
};

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
  auto promote_float(
    NativeType t_lhs, NativeType t_rhs,
    TypeOperandPriority t_enforce = TypeOperandPriority::PROMOTE_TO_LHS) const
    -> NativeTypeOpt;
  auto promote_int(
    NativeType t_lhs, NativeType t_rhs,
    TypeOperandPriority t_enforce = TypeOperandPriority::PROMOTE_TO_LHS) const
    -> NativeTypeOpt;
  auto promote_uint(
    NativeType t_lhs, NativeType t_rhs,
    TypeOperandPriority t_enforce = TypeOperandPriority::PROMOTE_TO_LHS) const
    -> NativeTypeOpt;

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
               TypeOperandPriority t_enforce = TypeOperandPriority::LEFT) const
    -> NativeTypeOpt;

  virtual ~TypePromoter() = default;
};
} // namespace semantic

#endif // CROW_CROW_SEMANTIC_TYPE_PROMOTER_HPP
