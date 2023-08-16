#!/usr/bin/env -S gawk -i inplace -f


# AWK script that replaces C++ header guards with an unique header guard
# Use at base of the project

# Example usage:
# ./header_guard.awk src/lexer/lexer.hpp src/parser/parser.hpp

# Generate header guard
function gen_hg()
{
	guard = toupper(FILENAME)
	gsub(/(\/)|(\.)/, "_", guard)
	gsub("SRC", "NEWLANG", guard)

	return guard
}

# Replace header guard definition with unique header guard
NR <= 2 && /^#(define|ifndef).+_HPP$/ {
		print $1, gen_hg();
		next
}

# Replace endif with generated header guard comment
FNR == NR && /^#endif.+_HPP$/ {
		print $1, "//", gen_hg()
		next
}

# Print the other lines
{
		print $0
}
