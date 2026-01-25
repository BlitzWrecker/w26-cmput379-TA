# Makefile to compile three example programs
all: process_creation parsing_and_matching data_structures popen_parsing_and_matching sscanf strstr

process_creation: process_creation.c
	gcc -Wall -o process_creation process_creation.c

parsing_and_matching: parsing_and_matching.c
	gcc -Wall -o parsing_and_matching parsing_and_matching.c

data_structures: data_structures.c
	gcc -Wall -o data_structures data_structures.c

popen_parsing_and_matching: popen_parsing_and_matching.c
	gcc -Wall -o popen_parsing_and_matching popen_parsing_and_matching.c

sscanf: strstr.c
	gcc -Wall -o sscanf sscanf.c

strstr: strstr.c
	gcc -Wall -o strstr strstr.c
	
clean:
	rm -f process_creation parsing_and_matching data_structures popen_parsing_and_matching sscanf strstr