all: gdb_example valgrind_example valgrind_exercise_source gdb_exercise gdb_exercise_soln

gdb_example: gdb_example.c
	gcc -g -o gdb_example gdb_example.c

valgrind_example: valgrind_example.c
	gcc -g -o valgrind_example valgrind_example.c

valgrind_exercise_source: valgrind_exercise_source.c
	gcc -g -o valgrind_exercise_source valgrind_exercise_source.c

gdb_exercise: gdb_exercise.c
	gcc -g -o gdb_exercise gdb_exercise.c

gdb_exercise_soln: gdb_exercise_soln.c
	gcc -g -o gdb_exercise_soln gdb_exercise_soln.c

clean:
	rm -f gdb_example valgrind_example valgrind_exercise_source gdb_exercise gdb_exercise_soln