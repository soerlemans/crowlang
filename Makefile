# Variables:
DEBUG := -DCMAKE_BUILD_TYPE=Debug
RELWITHDEBINFO := -DCMAKE_BUILD_TYPE=RelWithDebInfo

.DEFAULT_GOAL := build

# Rules:
.PHONY: all \
	build debug \
	install \
  clean clean-objects \
	format lint \
	docs docs-pdf

all: build debug
build: # Release build
	cmake -S . -B $@/
	cmake --build $@/

debug: # Build used for debugging and analyzing
	cmake -S . -B $@/ $(DEBUG)
	cmake --build $@/

# After build rules:
install: build
	@echo "TODO: Implement"

clean:
	rm -rf build/*
	rm -rf debug/*

clean-objects:
	rm -rf build/CMakeFiles/*
	rm -rf debug/CMakeFiles/*

# Misc. rules:
format:
	find src/ -iname "*.[ch]pp" -exec clang-format -i {} \;

lint:
	find src/ -iname "*.[ch]pp" -exec clang-tidy {} -- -DDEBUG \;

header_guard:
	PROJECT_NAME=CROW find src/ -iname "*.hpp" -exec ./tools/header_guard.awk {} \;

# Documentation rules:
docs:
	doxygen docs/Doxyfile

# Compile documentation as LaTex
docs-pdf: docs
	cd doxygen/latex/ && $(MAKE)
