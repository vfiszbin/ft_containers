#!/usr/bin/bash

SEED=42

execute_speed_test()
{
	START=$(date +%s.%N)
	time  > /dev/null 2>&1 "$1" "$2" 
	END=$(date +%s.%N)
	DIFF=$(echo "$END - $START" | bc)
	echo "$DIFF sec"
}


main()
{
	make
	echo "Seed: $SEED"
	echo "Running with std..."
	execute_speed_test ./bench_with_std $seed
	echo "Running with ft..."
	execute_speed_test ./bench_with_ft $seed
}

main "$@"