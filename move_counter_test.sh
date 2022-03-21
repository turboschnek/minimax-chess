#!/bin/bash

cd bin; \
	for i in 1 2 3 4 5 6; do 
		echo "-----------------test$i--------------------";
		./chess -c < ../$1/move_counter_test_in$i.txt;
		echo "correct:";
		tail -5 ../$1/move_counter_test_in$i.txt;
        echo $'\n';
	done