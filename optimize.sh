#!/bin/bash

fail(){
	echo "ERROR: ""$1"
	exit $2
}

main(){
	local bs="`dirname "$0"`"
	[ -f "${1:?no input file specified}" ] || fail "cannot find input file ""$1" 1
	local of="$2"
	if(($#==1)); then of="$1";echo "WARNING: changes will be written back to the original file"; fi
	touch "$of"
	if(($?!=0)); then fail "failed to create output file""$of" 1; fi
	local n="$1"
	local n1=${n%.cpp}
	local flg=0
	if [ a"$n" != a"$n1" ]; then
		if [ ! -f "$n1" ]; then flg=1; fi
		g++ "$n" -o "$n1" -Ofast -march=native
		if(($?!=0)); then fail "compile error, aborting" 2; fi
		strip "$n1"
		n="$n1"
	else
		[ -x "$n" ] || fail "input binary file ""$n"" does not have execute permission" 1
	fi
	if [ ! -f "$bs""/converter" ]; then
		g++ "$bs""/converter.cpp" -o "$bs""/converter" -O2
		if(($?!=0)); then fail "compile error, aborting" 2; fi
	fi
	"$bs""/converter" "$n" "$of"
	if((flg==1)); then rm "$n"; fi
}

main $@
