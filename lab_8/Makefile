EXECUTABLES = client server soln

all: $(EXECUTABLES)

client: client.c
	gcc -o client client.c

server: server.c
	gcc -o server server.c

soln: soln.c
	gcc -o soln soln.c

clean:
	rm -f $(EXECUTABLES)