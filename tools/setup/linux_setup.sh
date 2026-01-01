#!/usr/bin/env bash


# Globals:
readonly OS_RELEASE='/etc/os-release'

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

function ubuntu_install
{
    print_title 'Installing dependencies for Ubuntu.'

    log 'Installing build-system dependencies:'
    sudo apt install -y \
				 build-essential \
				 clang \
				 cmake extra-cmake-modules

    log 'Installing interoperability dependencies'
    # pipx install pybind11

    # We need the headers on the system.
    sudo apt install -y python3-pybind11 python3-dev

    log 'Installing dynamically linked dependencies:'

    # CLI11, Boost, LLVM and libclang  are dynamically linked.
    # And must be installed.
    sudo apt install -y \
				 libcurl4 \
				 libcli11-dev \
				 llvm-17-dev \
				 libboost-all-dev \
				 libzstd-dev
}

function debian_install
{
    print_title 'Installing dependencies for Debian.'

    log 'Installing build-system dependencies:'
    sudo apt install -y \
				 build-essential \
				 clang \
				 cmake extra-cmake-modules

    log 'Installing interoperability dependencies'
    # pipx install pybind11

    # We need the headers on the system.
    sudo apt install -y python3-pybind11 python3-dev

    log 'Installing dynamically linked dependencies:'

    # CLI11, Boost, LLVM and libclang  are dynamically linked.
    # And must be installed.
    sudo apt install -y \
				 libcurl4 \
				 libcli11-dev \
				 llvm-17-dev \
				 libboost-all-dev \
				 libzstd-dev
}

# Script:
if [[ ! -f "$OS_RELEASE" ]]
then
    err "'$OS_RELEASE' file not found."
fi

# Source the OS info from OS_RELEASE
source "$OS_RELEASE"

case "$ID" in
    ubuntu)
	ubuntu_install
	;;

    debian)
	debian_install
	;;

    *)
	err "Unsupported distro '$ID'."
	;;
esac

cat << EOF

Setup completed!
EOF
