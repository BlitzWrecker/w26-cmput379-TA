EXECUTABLES = popen read_integers read_and_find_a read_hello_world exercise_soln

all: $(EXECUTABLES)

exercise_soln: exercise_soln.c
	gcc exercise_soln.c -o exercise_soln

popen: popen.c
	gcc popen.c -o popen

read_integers: read_integers.c
	gcc read_integers.c -o read_integers

read_and_find_a: read_and_find_a.c
	gcc read_and_find_a.c -o read_and_find_a

read_hello_world: read_hello_world.c
	gcc read_hello_world.c -o read_hello_world

clean:
	rm -f $(EXECUTABLES)