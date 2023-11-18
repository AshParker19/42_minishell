#!/usr/bin/env bash

create_tests()
{
    n=1
    i=0
    while read line; do
	if [[ ${#line} -gt 0 ]]; then
		i=$((i+1))
		local test='test'
		test+="$n"
		echo $line >> $test 2>&1;
		mv $test $directory
		n=$((n+1))

	fi
    done < $filename
}

# Creating the tests
filename='tests.txt'
directory='test_list'
mkdir $directory
chmod +rwx $directory;
create_tests;
exit;
