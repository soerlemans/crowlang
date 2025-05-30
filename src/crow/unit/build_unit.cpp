#include "build_unit.hpp"


// Absolute Includes:
#include "lib/filesystem.hpp"

namespace unit {
BuildUnit::BuildUnit(BackendPtr&& t_backend, fs::path t_build_dir)
  : m_backend{std::move(t_backend)}, m_build_dir{t_build_dir}
{}

auto BuildUnit::compile(codegen::CompileParams& t_params) -> void
{
  m_backend->compile(t_params);
}

auto BuildUnit::build_dir() -> const fs::path&
{
  return m_build_dir;
}

// Functions:
auto make_build_unit(BuildUnitParams& t_params) -> BuildUnitPtr
{
  using codegen::InteropBackendType;
  using codegen::select_backend;

  BuildUnitPtr ptr{};

  auto& [backend_type, interop_types, opt] = t_params;

  // Get pointer to backend.
  auto backend_ptr{select_backend(backend_type)};

  // Instruct backend to add interop backends.
  for(const InteropBackendType type : interop_types) {
    backend_ptr->register_interop_backend(type);
  }

  // Set build dir.
  fs::path build_dir{};
  if(opt) {
    build_dir = opt.value();
  } else {
    build_dir = lib::temporary_directory();
  }

  ptr = std::make_shared<BuildUnit>(std::move(backend_ptr), build_dir);

  return ptr;
}
} // namespace unit
