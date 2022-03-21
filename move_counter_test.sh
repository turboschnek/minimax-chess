#!/bin/bash

cd bin; \
	results=();
	for i in {1..6}; do 
		results+=( "FAILED" );
		echo "-----------------test$i--------------------";
		output=$(./chess -c < ../$1/move_counter_test_in$i.txt);
		echo "${output}";
		echo "correct:";
		correct=$(tail -5 ../$1/move_counter_test_in$i.txt);
        echo "${correct}";
		echo "";
		tmpa=$(echo "${output}" | tail -1);
		tmpb=$(echo "${correct}" | tail -1);
		if [ "${tmpa}" = "${tmpb}" ]; then
			results[$i-1]="passed";
		fi
	done

	echo "-----------------overview------------------";
	for i in {1..6}; do 
		echo "test $i: ${results[$i-1]}";
	done
