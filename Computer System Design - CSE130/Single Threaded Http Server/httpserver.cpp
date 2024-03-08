#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <err.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){

	// declare ip, port, serverAddress
	char const *hostname = argv[1];
	int port = 80;
	struct sockaddr_in serverAddress;
	memset(&serverAddress, 0, sizeof serverAddress);

	// error handling for user defined arguments (port and ip)
	if (argc < 2 || argc > 3) {
		printf("Usage:\n");
		printf("  sudo ./httpserver <ip> [port]\n");
		exit(1);
	}
	if (argc == 3) {
		port = atoi(argv[2]);
	}

	// setup the port and ip in serverAddress
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	inet_aton(hostname, &serverAddress.sin_addr);

	// create a socket file descriptor
	int server_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock_fd == -1) {
		perror("socket()");
		exit(1);
	}

	// allow your socket to reuse a port/ip
	int opt = 1;
	int sockopt_result =  setsockopt(server_sock_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	if (sockopt_result == -1) {
		perror("setsockopt()");
		exit(1);
	}

	// bind the socket to the address and port number specified in serverAddress
	int bind_result = bind(server_sock_fd, (struct sockaddr*) &serverAddress, sizeof serverAddress);
	if (bind_result == -1) {
		perror("bind()");
		exit(1);
	}

	// make socket wait for a client to connect to the server
	int listen_result = listen(server_sock_fd, 500);
	if (listen_result < 0) {
		perror("listen()");
		exit(1);
	}

	// start of communication with the client
	while(1) {
		printf("Server is waiting ...\n");
		char buffer[4096];
		int addrLen = sizeof(serverAddress);

		// create a new socket and return a new file descriptor, connection is now established
		int client_sock_fd = accept(server_sock_fd, (struct sockaddr*) &serverAddress, (socklen_t*)&addrLen);
		if (client_sock_fd < 0) {
			perror("accept()");
			exit(1);
		}
		// read our new socket file descriptor into the buffer
		int recv_header = recv(client_sock_fd, buffer, 4096, 0);
		if (recv_header == -1) {
			perror("recv() on header");
			exit(1);
		}

		// check if the whole header is in the buffer
		char const *endDelim = "\r\n\r\n";
		bool found = false;
		while (found == false) {
			char *endHeader = strstr(buffer, endDelim);
			if (endHeader == NULL) {
				memset(buffer, 0, sizeof(buffer));
				recv_header = recv(client_sock_fd, buffer, 4096, 0);
				if (recv_header == -1) {
					perror("recv() on header");
					exit(1);
				}
			} else {
				found = true;
			}
		}

		char request[100];
		char slash_filename[100];
		char protocol[100];

		// load the respective header information into the buffer
		sscanf(buffer, "%s %s %s", request, slash_filename, protocol);

		// get rid of the slash that is always in the file name
		char* filename = slash_filename + 1;

		// check if valid http version -  505
		if (strcmp(protocol, "HTTP/1.1") != 0) {
			dprintf(client_sock_fd, "HTTP/1.1 505 HTTP Version Not Supported\r\nContent-Length: 0\r\n\r\n");
			close(client_sock_fd);
			continue;
		}

		// check if valid file name length - 400
		if (strlen(filename) != 10) {
			dprintf(client_sock_fd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n");
			close(client_sock_fd);
			continue;
		}

		// check if valid file name  - 400
		for (char * i = filename; *i; i++) {
			if (!isalnum(*i)) {
				dprintf(client_sock_fd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n");
				close(client_sock_fd);
				continue;
			}
		}

		// check if PUT/GET request - 400
		int get_req = strcmp(request, "GET");
		int put_req = strcmp(request, "PUT");
		if ((get_req != 0) && (put_req != 0)) {
			dprintf(client_sock_fd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n");
			close(client_sock_fd);
			continue;
		}

		// Process a PUT request
		if (strcmp(request, "PUT") == 0) {
			struct stat buf;
			int file_exist = stat(filename, &buf);
			char trash_conlen[100];
			char con_len[100];
			char const *needle = "Content-Length";
			// open the file for action
			int put_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (put_fd == -1) {
				// check if permissions to open file - 403
				dprintf(client_sock_fd, "HTTP/1.1 403 Forbidden\r\nContent-Length: 0\r\n\r\n");
				close(client_sock_fd);
				continue;
			}
			// extract the content length from the header
			char *token = strtok(buffer, "\r\n");
			while (token != NULL) {
				char *found = strstr(token, needle);
				if (found != NULL) {
					sscanf(token, "%s %s", trash_conlen, con_len);
				}
				token = strtok(NULL , "\r\n");
			}
			char put_buffer[32768];
			// if empty file or content length "0" - 201 or 200
			if (atoi(con_len) == 0) {
				write(put_fd, put_buffer, 0);
				if (file_exist == -1){
					dprintf(client_sock_fd, "HTTP/1.1 201 Created\r\nContent-Length: 0\r\n\r\n");
				} else {
					dprintf(client_sock_fd, "HTTP/1.1 200 Ok\r\nContent-Length: 0\r\n\r\n");
				}
				close(client_sock_fd);
				continue;
			}
			// receive the data from the socket and write it to our newly opened file descriptor
			int bytes_written = 0;
			int bytes_recv;
			while ((bytes_recv = recv(client_sock_fd, put_buffer, 1, 0)) != 0) {
				bytes_written += write(put_fd, put_buffer, bytes_recv);
				if (bytes_written == atoi(con_len)) {
					break;
				}
			}
			if (bytes_recv == -1) {
				// ran into errors receiving the data - 500
				dprintf(client_sock_fd, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n");
				close(put_fd);
				close(client_sock_fd);
				continue;
			}
			// all is good if we reached this point - 201 or 200
			if (file_exist == -1){
				dprintf(client_sock_fd, "HTTP/1.1 201 Created\r\nContent-Length: 0\r\n\r\n");
				close(put_fd);
				close(client_sock_fd);
				continue;
			} else {
				dprintf(client_sock_fd, "HTTP/1.1 200 Ok\r\nContent-Length: 0\r\n\r\n");
				close(put_fd);
				close(client_sock_fd);
				continue;
			}
		}

		// Process a GET request
		if (strcmp(request, "GET") == 0) {
			char get_buffer[4096];
			// open our file and check for the file size so we can include it in our content-length
			int f_desc = open(filename, O_RDONLY, S_IRWXU);
			struct stat finfo;
			int exist = fstat(f_desc, &finfo);
			int length = 0;
			if (exist == 0) {
				length = finfo.st_size;
			}
			if (f_desc == -1) {
				// check if file exists - if not respond 404
				if (exist == -1) {
					dprintf(client_sock_fd, "HTTP/1.1 404 Not Found\r\nContent-Length: %d\r\n\r\n", length);
					close(f_desc);
					close(client_sock_fd);
					continue;
				} else {
					// otherwise you don't have permissions - respond 403
					dprintf(client_sock_fd, "HTTP/1.1 403 Forbidden\r\nContent-Length: %d\r\n\r\n", length);
					close(f_desc);
					close(client_sock_fd);
					continue;
				}
			}			
			// read from our file and write it to the socket
			int bytes_read;
			int bytes_written = 0;
			bool respond = false;
			while ((bytes_read = read(f_desc, get_buffer, 1)) != 0) {
				if ((bytes_read != -1) && (respond == false)){
					respond = true;
					dprintf(client_sock_fd, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n", length);
				}
				bytes_written = write(client_sock_fd, get_buffer, 1);
			}
			// error reading file - 500
			if (bytes_read == -1) {
				dprintf(client_sock_fd, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: %d\r\n\r\n", length);
				close(f_desc);
				close(client_sock_fd);
				continue;
			}
			close(f_desc);
			close(client_sock_fd);
			continue;
		}
	}
}
