#include "type_promoter.hpp"

// STL Includes:
#include <sstream>

// Absolute Includes:
#include "crow/debug/log.hpp"
#include "crow/diagnostic/diagnostic_error.hpp"

namespace semantic {
// Methods:
auto TypePromoter::get_priority(const TypeLadder& t_ladder,
                                const NativeType t_type) const
  -> TypeLadder::mapped_type
{
  using diagnostic::diagnostic_error;

  TypeLadder::mapped_type priority{0};

  const auto iter{t_ladder.find(t_type)};
  if(iter != t_ladder.end()) {
    priority = iter->second;
  } else {
    std::stringstream ss;

    ss << "NativeType does not exist in floating point TypeLadder.\n";
    ss << "Did not find " << t_type << '\n';

    diagnostic_error(ss.str());
  }

  return priority;
}

TypePromoter::TypePromoter(): m_float{2}, m_int{10}, m_uint{10}
{
  // Float:
  m_float.insert({NativeType::F32, 0});
  m_float.insert({NativeType::F64, 1});

  // Integer:
  m_int.insert({NativeType::INT, 0});
  m_int.insert({NativeType::I8, 1});
  m_int.insert({NativeType::I16, 2});
  m_int.insert({NativeType::I32, 3});
  m_int.insert({NativeType::I64, 4});
  m_int.insert({NativeType::ISIZE, 5});

  // Unsigned Integer:
  m_uint.insert({NativeType::UINT, 0});
  m_uint.insert({NativeType::U8, 1});
  m_uint.insert({NativeType::U16, 2});
  m_uint.insert({NativeType::U32, 3});
  m_uint.insert({NativeType::U64, 4});
  m_uint.insert({NativeType::USIZE, 5});
}

auto TypePromoter::promote_bool(const NativeType t_lhs) const -> NativeTypeOpt
{
  NativeTypeOpt opt;

  const auto integer{m_int.contains(t_lhs)};
  const auto unsigned_integer{m_uint.contains(t_lhs)};

  // Only integers may be promoted to boolean's.
  if(integer || unsigned_integer) {
    opt = NativeType::BOOL;
  }

  return opt;
}

auto TypePromoter::promote_float(const NativeType t_lhs, const NativeType t_rhs,
                                 const bool enforce_lhs) const -> NativeTypeOpt
{
  NativeTypeOpt opt;

  // TODO: Handle Int and UInt to float promotion.
  const auto lhs_priority{get_priority(m_float, t_lhs)};
  const auto rhs_priority{get_priority(m_float, t_rhs)};

  if(lhs_priority > rhs_priority) {
    opt = t_lhs;
  } else if(!enforce_lhs) {
    opt = t_rhs;
  }

  return opt;
}

auto TypePromoter::promote_int(const NativeType t_lhs, const NativeType t_rhs,
                               const bool enforce_lhs) const -> NativeTypeOpt
{
  NativeTypeOpt opt;

  const auto lhs_priority{get_priority(m_int, t_lhs)};
  const auto rhs_priority{get_priority(m_int, t_rhs)};

  if(lhs_priority > rhs_priority) {
    opt = t_lhs;
  } else if(!enforce_lhs) {
    opt = t_rhs;
  }

  return opt;
}

auto TypePromoter::promote_uint(const NativeType t_lhs, const NativeType t_rhs,
                                const bool enforce_lhs) const -> NativeTypeOpt
{
  NativeTypeOpt opt;

  // TODO: Handle Int to UInt type promotion.
  const auto lhs_priority{get_priority(m_uint, t_lhs)};
  const auto rhs_priority{get_priority(m_uint, t_rhs)};

  if(lhs_priority > rhs_priority) {
    opt = t_lhs;
  } else if(!enforce_lhs) {
    opt = t_rhs;
  }

  return opt;
}

auto TypePromoter::promote(const NativeType t_lhs, const NativeType t_rhs,
                           const bool enforce_lhs) const -> NativeTypeOpt
{
  NativeTypeOpt opt;

  const auto in_ladder{[&](const TypeLadder& t_ladder) {
    const auto lhs{t_ladder.contains(t_lhs)};
    const auto rhs{t_ladder.contains(t_rhs)};

    return lhs && rhs;
  }};

  // if(m_float.contains(t_lhs) || m_float.contains(t_rhs)) {
  //   opt = promote_float(t_lhs, t_rhs);
  // } else

  if(in_ladder(m_int)) {
    opt = promote_int(t_lhs, t_rhs, enforce_lhs);
  } else if(in_ladder(m_uint)) {
    opt = promote_uint(t_lhs, t_rhs, enforce_lhs);
  }

  return opt;
}
} // namespace semantic
