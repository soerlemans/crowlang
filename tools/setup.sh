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

function debian_install
{
    print_title 'Installing dependencies for Debian.'

    log 'Installing build-system dependencies:'
    sudo apt install -y \
	 clang \
	 cmake extra-cmake-modules

    log 'Installing interoperability dependencies'
    pipx install pybind11

    log 'Installing dynamically linked dependencies:'
    sudo apt install -y \
	 libcurl4 \
	 libcli11-dev \
	 llvm-17-dev libclang-17-dev liblld-17-dev \
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
    debian)
	debian_install
	;;

    *)
	err "Unsupported distro '$ID'."
	;;
esac
