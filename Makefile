# Variables:
DEBUG := -DCMAKE_BUILD_TYPE=Debug
RELDEBUG := -DCMAKE_BUILD_TYPE=RelWithDebInfo
TESTS := -DBUILD_CROW_TESTS=TRUE

CLANG_TIDY_ARGS := -header-filter=src/.* -extra-arg=-std=c++2b

.DEFAULT_GOAL := build

# Rules:
.PHONY: all \
	build debug reldebug tests\
	install \
  clean clean-objects \
	format lint \
	docs docs-pdf

all: build debug reldebug tests
build: # Release build.
	cmake -S . -B $@/
	cmake --build $@/

debug: # Build used for debugging and analyzing.
	cmake -S . -B $@/ $(DEBUG)
	cmake --build $@/

reldebug: # Build combination of release with debug info.
	cmake -S . -B $@/ $(RELDEBUG)
	cmake --build $@/

tests: # Build used for creating tests.
	cmake -S . -B $@/ $(TESTS)
	cmake --build $@/

# After build rules:
install: build
	@echo "TODO: Implement"

clean:
	rm -rf build/*
	rm -rf debug/*
	rm -rf reldebug/*
	rm -rf tests/*

clean-objects:
	rm -rf build/CMakeFiles/*
	rm -rf debug/CMakeFiles/*
	rm -rf reldebug/CMakeFiles/*
	rm -rf tests/CMakeFiles/*

# Misc. rules:
format:
	find src/ -iname "*.[ch]pp" -exec clang-format -i {} \;

lint:
	find src/ -iname "*.[ch]pp" -exec clang-tidy $(CLANG_TIDY_ARGS) {} -- -DDEBUG \;

header_guard:
	PROJECT_NAME=CROW find src/ -name "*.hpp" -exec ./tools/header_guard.awk {} \;

# Documentation rules:
docs:
	doxygen .doxyfile

# Compile documentation as LaTex
docs-pdf: docs
	cd doxygen/latex/ && $(MAKE)
