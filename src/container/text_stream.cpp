#include "text_stream.hpp"


using namespace container;


auto TextStream::next_line() -> void
{
  while(current() != '\n' && !eos()) {
		next();
  }
}
