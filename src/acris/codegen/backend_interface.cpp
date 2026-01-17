#include "backend_interface.hpp"

// Relative Includes:
#include "cpp_backend/cpp_backend.hpp"
#include "llvm_backend/llvm_backend.hpp"

namespace codegen {
auto select_backend(const BackendType t_selector) -> BackendPtr
{
  using cpp_backend::CppBackend;
  using llvm_backend::LlvmBackend;

  BackendPtr ptr{};

  switch(t_selector) {
    case BackendType::LLVM_BACKEND: {
      ptr = std::make_shared<LlvmBackend>();
      break;
    }

    case BackendType::CPP_BACKEND: {
      ptr = std::make_shared<CppBackend>();
      break;
    }

    default:
      const auto err_msg{
        std::format("Unsupported codegeneration backend \"{}\"",
                    backendtype2str(t_selector))};
      throw std::invalid_argument{err_msg};
      break;
  }

  return ptr;
}

auto backendtype2str(BackendType t_type) -> std::string_view
{
  switch(t_type) {
    case BackendType::CPP_BACKEND:
      return "cpp";

    case BackendType::LLVM_BACKEND:
      return "llvm";

    default:
      throw std::invalid_argument{
        "backendtype2str() could not convert BackendType to string."};
      break;
  }

  return {};
}
} // namespace codegen

auto operator<<(std::ostream& t_os, codegen::BackendType t_type)
  -> std::ostream&
{
  using codegen::backendtype2str;

  t_os << backendtype2str(t_type);

  return t_os;
}
