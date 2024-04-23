#  Copyright (C) 2003,2004,2005,2006 Free Software Foundation, Inc.
#  Contributed by Kelley Cook, June 2004.
#  Original code from Neil Booth, May 2003.
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 2, or (at your option) any
# later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

# This Awk script reads in the option records generated from 
# opt-gather.awk, combines the flags of duplicate options and generates a
# C header file.
#
# This program uses functions from opt-functions.awk
# Usage: awk -f opt-functions.awk -f opth-gen.awk < inputfile > options.h

BEGIN {
	n_opts = 0
	n_langs = 0
	n_extra_masks = 0
	quote = "\042"
	comma = ","
	FS=SUBSEP
}

# Collect the text and flags of each option into an array
	{
		if ($1 == "Language") {
			langs[n_langs] = $2
			n_langs++;
		}
		else {
			name = opt_args("Mask", $1)
			if (name == "") {
				opts[n_opts]  = $1
				flags[n_opts] = $2
				help[n_opts]  = $3
				n_opts++;
			}
			else {
				extra_masks[n_extra_masks++] = name
			}
		}
	}

# Dump out an enumeration into a .h file.
# Combine the flags of duplicate options.
END {
print "/* This file is auto-generated by opts.sh.  */"
print ""
print "#ifndef OPTIONS_H"
print "#define OPTIONS_H"
print ""
print "extern int target_flags;"
print ""

for (i = 0; i < n_opts; i++) {
	name = var_name(flags[i]);
	if (name == "")
		continue;

	print "extern " var_type(flags[i]) name ";"
}
print ""

for (i = 0; i < n_opts; i++) {
	name = opt_args("Mask", flags[i])
	vname = var_name(flags[i])
	mask = "MASK_"
	if (vname != "") {
		mask = "OPTION_MASK_"
	}
	if (name != "" && !flag_set_p("MaskExists", flags[i]))
		print "#define " mask name " (1 << " masknum[vname]++ ")"
}
for (i = 0; i < n_extra_masks; i++) {
	print "#define MASK_" extra_masks[i] " (1 << " masknum[""]++ ")"
}

for (var in masknum) {
	if (masknum[var] > 31) {
		if (var == "")
			print "#error too many target masks"
		else
			print "#error too many masks for " var
	}
}
print ""

for (i = 0; i < n_opts; i++) {
	name = opt_args("Mask", flags[i])
	vname = var_name(flags[i])
	macro = "OPTION_"
	mask = "OPTION_MASK_"
	if (vname == "") {
		vname = "target_flags"
		macro = "TARGET_"
		mask = "MASK_"
	}
	if (name != "" && !flag_set_p("MaskExists", flags[i]))
		print "#define " macro name \
		      " ((" vname " & " mask name ") != 0)"
}
for (i = 0; i < n_extra_masks; i++) {
	print "#define TARGET_" extra_masks[i] \
	      " ((target_flags & MASK_" extra_masks[i] ") != 0)"
}
print ""

for (i = 0; i < n_opts; i++) {
	opt = opt_args("InverseMask", flags[i])
	if (opt ~ ",") {
		vname = var_name(flags[i])
		macro = "OPTION_"
		mask = "OPTION_MASK_"
		if (vname == "") {
			vname = "target_flags"
			macro = "TARGET_"
			mask = "MASK_"
		}
		print "#define " macro nth_arg(1, opt) \
		      " ((" vname " & " mask nth_arg(0, opt) ") == 0)"
	}
}
print ""

for (i = 0; i < n_langs; i++) {
	macros[i] = "CL_" langs[i]
	gsub( "[^A-Za-z0-9_]", "X", macros[i] )
	s = substr("            ", length (macros[i]))
	print "#define " macros[i] s " (1 << " i ")"
    }

print ""
print "enum opt_code"
print "{"
	
for (i = 0; i < n_opts; i++)
	back_chain[i] = "N_OPTS";

for (i = 0; i < n_opts; i++) {
	# Combine the flags of identical switches.  Switches
	# appear many times if they are handled by many front
	# ends, for example.
	while( i + 1 != n_opts && opts[i] == opts[i + 1] ) {
		flags[i + 1] = flags[i] " " flags[i + 1];
		i++;
	}

	len = length (opts[i]);
	enum = "OPT_" opts[i]
	if (opts[i] == "finline-limit=")
		enum = enum "eq"
	gsub ("[^A-Za-z0-9]", "_", enum)

	# If this switch takes joined arguments, back-chain all
	# subsequent switches to it for which it is a prefix.  If
	# a later switch S is a longer prefix of a switch T, T
	# will be back-chained to S in a later iteration of this
	# for() loop, which is what we want.
	if (flag_set_p("Joined.*", flags[i])) {
		for (j = i + 1; j < n_opts; j++) {
			if (substr (opts[j], 1, len) != opts[i])
				break;
			back_chain[j] = enum;
		}
	}

	s = substr("                                     ", length (opts[i]))
	if (i + 1 == n_opts)
		comma = ""

	if (help[i] == "")
		hlp = "0"
	else
		hlp = "N_(\"" help[i] "\")";

	print "  " enum "," s "/* -" opts[i] " */"
}

print "  N_OPTS"
print "};"
print ""
print "#endif /* OPTIONS_H */"
}
