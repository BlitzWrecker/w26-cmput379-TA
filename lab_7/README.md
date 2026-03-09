# Lab 7 Demo Code
There four parts:
1. A TCP client-server pair exchanging text messages.
2. A TCP client-server pair where the server transmits a file.
3. A UDP sender-receiver pair where the sender streams PCM audio data to the client, which plays the audio.
4. The exercise solution, which is a fork-based server.

## Text-based client-server
Files: `msg_server.c` and `msg_client.c`.

Usage:
```bash
# Start the server first
$ ./msg_server <port>

# On a separate terminal instance, start the client
$ ./msg_client <hostname> <port>

# Follow the onscreen prompts
```

The server and client should have the same `<port>`. For communication between two prcesses on the same host, replace `<hostname>` with `127.0.0.1`. For example:
```bash
$ ./msg_server 5000

# On a separate terminal instance
$ ./msg_client 127.0.0.1 5000
```

## Genertic byte stream client-server
Files: `tcp_file_server.c` and `tcp_file_client.c`.

Usage:
```bash
# Start the server first
$ ./tcp_file_server <port> /path/to/in_file

# On a separate terminal instance, start the client
$ ./tcp_file_client <hostname> <port> /path/to/out_file
```

The server reads the content of `path/to/in_file` and transmits the content over the socket, where the client receives it and saves the content to `/path/to/out_file`. For example:
```bash
# Assume lab_07_ualberta.png is in the current directory
$ ./tcp_file_server 5000 lab_07_ualberta.png

# On a separate terminal instance
$ ./tcp_file_client 127.0.0.1 5000 received_file.png
```

## UDP audio playback
Files: `udp_sender.c` and `udp_receiver.c`.

Usage:
```bash
# Start the receiver first
$ ./udp_receiver <port>

# On a separate terminal instance, start the sender
$ ./udp_sender <hostname> <port> /file/to/send
```
`udp_receiver.c` implements a simple audio player that streams audio received from the sender. Only MP3 files are supported. For example:
```bash
$ ./udp_receiver 5000

# On a separate terminal instance
$ ./udp_sender 127.0.0.1 5000 lab_07_alla-turca.mp3
```
If ran locally, i.e. not over SSH, you should hear music playing. The audio is clicky and choppy. This is the nature of UDP.

## Exercise
The exercise is to modify `msg_server.c` to fork a new process to handle each accepted connection. 

File: `msg_fork_server.c`

Usage:
```bash
# Start the server first
$ ./msg_fork_server <port>

# On separate terminal instances, start the client
$ ./msg_client <hostname> <port>

# Follow the onscreen prompts.
```