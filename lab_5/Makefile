CC=gcc
CFLAGS=-Wall
EXECUTABLES=example1 example2 example3 file_stdin file_stdout kv_storage_unidirectional kv_storage_bidirectional

all: $(EXECUTABLES)

example1: example1.c
	$(CC) $(CFLAGS) example1.c -o example1

example2: example2.c
	$(CC) $(CFLAGS) example2.c -o example2

example3: example3.c
	$(CC) $(CFLAGS) example3.c -o example3

file_stdin: file_stdin.c
	$(CC) $(CFLAGS) file_stdin.c -o file_stdin

file_stdout: file_stdout.c
	$(CC) $(CFLAGS) file_stdout.c -o file_stdout

kv_storage_unidirectional: kv_storage_unidirectional.c
	$(CC) $(CFLAGS) kv_storage_unidirectional.c -o kv_storage_unidirectional

kv_storage_bidirectional: kv_storage_bidirectional.c
	$(CC) $(CFLAGS) kv_storage_bidirectional.c -o kv_storage_bidirectional

clean:
	rm -f $(EXECUTABLES)
