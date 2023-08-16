#include "trace.hpp"

// STL Includes:
#include <cstddef>
#include <iomanip>
#include <sstream>


// Only facilitate Trace if we are on the DEBUG build
#if DEBUG

// Methods:
auto Trace::indent_text() -> std::string
{
  std::stringstream ss;
  if(m_counter > 0) {
    ss << " " << std::string(m_counter, ' ');
  } else {
    ss << "#.";
  }

  ss << "─> ";

  return ss.str();
}

// Destructor:
Trace::~Trace()
{
  if(m_print) {
    m_counter--;
  }
}

#endif // DEBUG
