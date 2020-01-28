default: part1 part2

part1: assignment2_part1.c
	gcc -o part1.out assignment2_part1.c -pthread

part2: processQueue.c assignment2_part2.c processQueue.h
	gcc -o part2.out processQueue.c assignment2_part2.c 

clean: 
	rm *.out
	rm cpu_scheduling_output_file.txt
