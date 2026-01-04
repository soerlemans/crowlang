# Add source files
target_sources(${TARGET_CROW_LIB} PRIVATE
	loglevel.cpp
	trace.cpp
)

# Included a lot, rarely changes.
target_precompile_headers(${TARGET_CROW_LIB} PRIVATE
  log.hpp
)
