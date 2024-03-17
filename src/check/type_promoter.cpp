#include "type_promoter.hpp"

// Includes:
#include "../debug/log.hpp"

namespace check {
// Methods:
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
  m_int.insert({NativeType::UINT, 0});
  m_uint.insert({NativeType::U8, 1});
  m_uint.insert({NativeType::U16, 2});
  m_uint.insert({NativeType::U32, 3});
  m_uint.insert({NativeType::U64, 4});
  m_uint.insert({NativeType::USIZE, 5});
}

auto TypePromoter::promote_bool(const NativeType t_lhs) const -> NativeTypeOpt
{
  NativeTypeOpt opt;

  return opt;
}

auto TypePromoter::promote_float(const NativeType t_lhs,
                                 const NativeType t_rhs) const -> NativeTypeOpt
{
  NativeTypeOpt opt;

  return opt;
}

auto TypePromoter::promote_int(const NativeType t_lhs,
                               const NativeType t_rhs) const -> NativeTypeOpt
{
  NativeTypeOpt opt;

  const auto lhs{m_int.find(t_lhs)};
  const auto rhs{m_int.find(t_rhs)};

  // TODO: Use error handling?
  if(lhs != m_int.end() && rhs != m_int.end()) {
    if(lhs->second > rhs->second) {
      opt = lhs->first;
    } else {
      opt = rhs->first;
    }
  }

  return opt;
}

auto TypePromoter::promote_uint(const NativeType t_lhs,
                                const NativeType t_rhs) const -> NativeTypeOpt
{
  NativeTypeOpt opt;

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
    opt = promote_int(t_lhs, t_rhs);
  } else if(in_ladder(m_uint)) {
    opt = promote_uint(t_lhs, t_rhs);
  }

  return opt;
}
} // namespace check
