#ifndef ACRIS_ACRIS_MIR_OPERAND_HPP
#define ACRIS_ACRIS_MIR_OPERAND_HPP

// STL Includes:
#include <memory>
#include <variant>
#include <vector>

namespace mir {
// Using:
using types::core::NativeType;
using types::core::TypeVariant;

// Forward Declarations:
struct Literal;
struct SsaVar;
struct Label;
struct Instruction;
struct BasicBlock;
struct Function;
struct Module;

class Operand;

// Aliases:
using SsaVarPtr = std::shared_ptr<SsaVar>;
using OperandVariant = std::variant<SsaVarPtr, Literal, Label>;
using OperandSeq = std::vector<Operand>;

// Classes:
class Operand {
  private:
  OperandVariant m_operand_types;

  public:
};

} // namespace mir

#endif // ACRIS_ACRIS_MIR_OPERAND_HPP
