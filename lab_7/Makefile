EXECUTABLES = tcp_file_server udp_receiver udp_sender tcp_file_client msg_fork_server msg_server msg_client

all: $(EXECUTABLES)

tcp_file_server: tcp_file_server.c
	gcc -o tcp_file_server tcp_file_server.c

tcp_file_client: tcp_file_client.c
	gcc -o tcp_file_client tcp_file_client.c

udp_receiver: udp_receiver.c
	gcc -o udp_receiver udp_receiver.c -lasound

udp_sender: udp_sender.c
	gcc -o udp_sender udp_sender.c -lasound

msg_server: msg_server.c
	gcc -o msg_server msg_server.c

msg_client: msg_client.c
	gcc -o msg_client msg_client.c

msg_fork_server: msg_fork_server.c
	gcc -o msg_fork_server msg_fork_server.c

clean:
	rm -f $(EXECUTABLES)