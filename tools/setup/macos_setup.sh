#!/usr/bin/env bash


# Functions:
function err
{
    echo "Error: ${1:?Error: Must pass error message to err function}" >&2
    exit "${2:-1}"
}

function print_border
{
    local ARG_ERROR='Error: Must pass at least one numerical argument to print_border().'
    local COUNT="${1:?$ARG_ERROR}"

    # Convert a COUNT of spaces to '='.
    printf "%*s\n" "$COUNT" | tr ' ' '='
 }

function print_title
{
    local ARG_ERROR='Error: Must pass at least one argument to print_title().'
    local TITLE="${@:?$ARG_ERROR}"
    local FULL_COUNT="$(echo "$TITLE" | wc -c)"
    local COUNT="$(($FULL_COUNT - 1))"

    echo "$TITLE"
    print_border "$COUNT"
}

function log
{
    echo "[+] $@"
}

function macos_install
{
    print_title 'Installing dependencies for MacOs.'

    log 'Check installed Xcode version:'
    /usr/bin/xcodebuild -version || err "XCode not installed" 1

    log 'Installing build-system dependencies:'

    brew install cmake extra-cmake-modules

    log 'Installing interoperability dependencies'
    # pipx install pybind11

    # We need the headers on the system.
    # sudo apt install -y python3-pybind11 python3-dev

    log 'Installing dynamically linked dependencies:'

    # CLI11, Boost, LLVM and libclang  are dynamically linked.
    # And must be installed.
    # sudo apt install -y \
	# 			 libcurl4 \
	# 			 libcli11-dev \
	# 			 llvm-17-dev \
	# 			 libboost-all-dev \
	# 			 libzstd-dev

    brew install boost

    # TODO: Add the rest of the deps.
}

# Script:
macos_install

cat << EOF

Setup completed!
EOF
