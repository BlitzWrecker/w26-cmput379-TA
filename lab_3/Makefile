all: gdb_example valgrind_example gdb_exercise_source valgrind_exercise valgrind_exercise_soln

gdb_example: gdb_example.c
	gcc -g -o gdb_example gdb_example.c

valgrind_example: valgrind_example.c
	gcc -g -o valgrind_example valgrind_example.c

gdb_exercise_source: gdb_exercise_source.c
	gcc -g -o gdb_exercise_source gdb_exercise_source.c

valgrind_exercise: valgrind_exercise.c
	gcc -g -o valgrind_exercise valgrind_exercise.c

valgrind_exercise_soln: valgrind_exercise_soln.c
	gcc -g -o valgrind_exercise_soln valgrind_exercise_soln.c

clean:
	rm -f gdb_example valgrind_example gdb_exercise_source valgrind_exercise valgrind_exercise_soln