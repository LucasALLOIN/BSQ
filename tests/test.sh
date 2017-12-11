#!/bin/bash

touch gen_test
count=$(ls mouli_maps | wc -l)
ls mouli_maps > gen_test

for i in `seq 1 $count`; do
    t=$(sed "$i!d" gen_test)
    echo -n "Test $t: " 
    ../bsq mouli_maps/$t > comp1
    diff=$(diff comp1 mouli_maps_solved/$t)
    if [ "$diff" == "" ]
    then
	echo -e "\e[32mOK\e[0m"
    else
	echo -e "\e[31mFailed\e[0m"
    fi
done
rm gen_test
