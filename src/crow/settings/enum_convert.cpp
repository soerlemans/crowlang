#include "enum_convert.hpp"

// STL Includes
#include <exception>
#include <string>

// Internal:
namespace {
using codegen::BackendType;
using debug::LogLevel;
using settings::BackendTypeMap;
using settings::LogLevelMap;

LogLevelMap loglevel_convmap{
  {"critical", LogLevel::CRITICAL},
  {   "error",    LogLevel::ERROR},
  { "warning",  LogLevel::WARNING},
  {  "notice",   LogLevel::NOTICE},
  {    "info",     LogLevel::INFO},
  { "verbose",  LogLevel::VERBOSE}
};

BackendTypeMap backendtype_convmap{
  { "cpp",  BackendType::CPP_BACKEND},
  {"llvm", BackendType::LLVM_BACKEND},
};
} // namespace

namespace settings {
[[nodiscard("Pure function must use result.")]]
auto loglevel_map() -> const LogLevelMap&
{
  return loglevel_convmap;
}

[[nodiscard("Pure function must use result.")]]
auto str2loglevel(const std::string_view t_key) -> debug::LogLevel
{
  using debug::LogLevel;

  LogLevel level{};

  const auto& map{loglevel_map()};
  std::string str{t_key};

  auto iter{map.find(str)};
  if(iter != map.end()) {
    level = iter->second;
  } else {
    throw std::invalid_argument{
      "str2loglevel() could not convert string to LogLevel."};
  }

  return level;
}

[[nodiscard("Pure function must use result.")]]
auto backendtype_map() -> const BackendTypeMap&
{
  return backendtype_convmap;
}

[[nodiscard("Pure function must use result.")]]
auto str2backendtype(const std::string_view t_key) -> codegen::BackendType
{
  using codegen::BackendType;

  BackendType backend{};

  const auto& map{backendtype_map()};
  std::string str{t_key};

  auto iter{map.find(str)};
  if(iter != map.end()) {
    backend = iter->second;
  } else {
    throw std::invalid_argument{
      "str2backendtype could not convert string to BackendType."};
  }

  return backend;
}
} // namespace settings
