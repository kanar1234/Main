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
#include <dirent.h>
#include <string>
#include <vector>
#include <algorithm>

struct ThreadBuffer {
	//constant text
	//const char constBackup[100] = "backup-";
	//stores the time
	char timeNow[100];
	//for easy access to all backup names
	std::vector<std::string> savedBackupNames;
	//store the current backup name
	char currentBackupName[100];
	//tracks number of backups created
	int tracker = 0;
};

struct httpObject {
	char buffer[4096];
	char request[100];
	char slash_filename[100];
	char backup_timestamp[100];
	char protocol[100];
	char* filename;
	int content_length;
	int status_code;
};

// Create a backup copy of the server directory
void createBackup(int client_sock_fd, struct ThreadBuffer* clients){
	//create directory
	int i;
	printf("constBackup is backup-\n");
	int t = (int)time(NULL);
	printf("got the time: %d\n", t);
	char time[100];
	sprintf(time, "%d", t);
	printf("string time is %s\n", time);
	char current_backup[100];
	strcpy(current_backup, "backup-");
	strcat(current_backup, time);
	printf("constBackup+timeNow is %s\n", current_backup);
	int check;
	check = mkdir(current_backup, 0777);

  // check if directory is created or not
  if (!check)
      printf("Directory created\n");
  else {
      printf("Directory already exists\n");
  }

	//copy all files in the server to the backup folder
	int src_fd, dst_fd, n, err, ch;
	bool hasPeriod = false;
	//used for opening a directory
	struct dirent *sd;
	char backupFileName[100] = "";
	unsigned char backupBuf[4096];
	//for checking if we're opening a directory
	struct stat statBuf;

	DIR *dir;
	//open current directory
	dir = opendir(".");
	if(dir == NULL)
	{
		// printf("How is opening the current directory even NULL?");
	}

	// Loop through server directory looking for valid files to copy
	while((sd = readdir(dir)) != NULL)
	{
		src_fd = open(sd->d_name, O_RDONLY);
		if (fstat(src_fd, &statBuf) != 0)
		{
			//printf("fstat() failed\n");
		}
		hasPeriod = false;
		for(i = 0; i < strlen(sd->d_name); i++)
		{
			if(sd->d_name[i] == '.')
			{
				//printf("%s has . in the name\n", sd->d_name);
				hasPeriod = true;
			}
		}

		if(S_ISDIR(statBuf.st_mode))
		{
			//printf("%s is a directory\n", sd->d_name);
		}
		else if(hasPeriod)
		{
			//printf("%s has . in the name\n", sd->d_name);
		}
		else if(src_fd == -1)
		{
			//printf("%can not open s\n, permission error", sd->d_name);
		}
		else if(strlen(sd->d_name) != 10)
		{
			//printf("length of %s is: %d\n", sd->d_name, strlen(sd->d_name));
		}
		else // Valid file found -> create backup
		{
			memset(backupFileName, 0, sizeof backupFileName);
			printf("%s is a file\n", sd->d_name);
			strcat(backupFileName, current_backup);
			strcat(backupFileName, "/");
			strcat(backupFileName, sd->d_name);
			printf("backupFileName is %s\n", backupFileName);

			//copy file to backup folder
			dst_fd = open(backupFileName, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (dst_fd == -1) {
				// check if permissions to open file - 403
				dprintf(client_sock_fd, "HTTP/1.1 403 Forbidden\r\nContent-Length: 0\r\n\r\n");
				close(client_sock_fd);
				close(dst_fd);
				return;
			}

			while(read(src_fd,&ch,1))
			{
				write(dst_fd,&ch,1);
			}
			close(dst_fd);
		}
		close(src_fd);
	}
	dprintf(client_sock_fd, "HTTP/1.1 201 Created\r\nContent-Length: 0\r\n\r\n");
	closedir(dir);
	//printf("out of the loop\n\n");
	//store directory name in char array
	std::string newFile (time);
	clients->savedBackupNames.push_back(newFile);
	//printf("saved name\n");
	clients->tracker++;

	close(client_sock_fd);
	return;
}

// Recover a server state from a backup copy
void recover(int client_sock_fd, struct ThreadBuffer* clients, char* timestamp) {
	std::string copy = (timestamp);
	int found = 0;
	if((found = std::count(clients->savedBackupNames.begin(), clients->savedBackupNames.end(), copy)) == 0) {
		copy = clients->savedBackupNames.back();
	}
	const char* c_copy = copy.c_str();
	if(strcmp(timestamp, "-1") == 0) {
		// No timestamp given
	}
	else if(found == 0) {
		// Couldn't find timestamp
		dprintf(client_sock_fd, "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
		close(client_sock_fd);
		return;
	}

	// copy all files in the server to the backup folder
	int src_fd, dst_fd, ch;
	//used for opening a directory
	struct dirent *sd;

	// unsigned char backup_buf[4096];
	//for checking if we're opening a directory
	struct stat statBuf;

	char backup_directory[100] = "";
	strcat(backup_directory, "backup-");
	strcat(backup_directory, c_copy);
	strcat(backup_directory, "/");

	DIR *backup_dir;
	DIR *dir;
	//open current directory
	dir = opendir(".");
	int backup_fd = open(backup_directory, O_RDONLY);
	backup_dir = fdopendir(backup_fd);
	if(dir == NULL) {
		dprintf(client_sock_fd, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n");
		close(client_sock_fd);
		return;
	}
	if(backup_dir == NULL) {
		dprintf(client_sock_fd, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n");
		close(client_sock_fd);
		return;
	}

	// Empty the server directory
	while((sd = readdir(dir)) != NULL) {
		src_fd = open(sd->d_name, O_RDWR);
		if (fstat(src_fd, &statBuf) != 0) {
			//printf("fstat() failed\n");
		}
		if(S_ISDIR(statBuf.st_mode)) {
			//printf("%s is a directory\n", sd->d_name);
		}
		else if(sd->d_name[0] == '.') {
			//printf("%s has . in the first character of the name\n", sd->d_name);
		}
		else if(src_fd == -1) {
			//printf("%s can not open\n", sd->d_name);
		}
		else if(strlen(sd->d_name) != 10) {
			//printf("%s is invalid size\n", sd->d_name);
		}
		else if(strcmp("httpserver", sd->d_name) == 0) {
			//printf("%s is the server binary\n", sd->d_name);
		}
		else {
			remove(sd->d_name);
		}
		close(src_fd);
	}
	// Place files from the backup in the server directory
	while((sd = readdir(backup_dir)) != NULL) {
		char cpy_file[100] = "";
		strcat(cpy_file, backup_directory); // cpy_file = backup-[timestamp]
		strcat(cpy_file, sd->d_name); // cpy_file = backup-[timestamp]/[filename]
		src_fd = open(cpy_file, O_RDWR);
		if (fstat(src_fd, &statBuf) != 0) {
			//printf("fstat() failed\n");
		}
		if(S_ISDIR(statBuf.st_mode)) {
			//printf("%s is a directory\n", sd->d_name);
		}
		else if(sd->d_name[0] == '.') {
			//printf("%s has . in the first character of the name\n", sd->d_name);
		}
		else if(src_fd == -1) {
			//printf("%s can not open s\n", sd->d_name);
		}
		else if(strlen(sd->d_name) != 10) {
			//printf("%s is invalid size\n", sd->d_name);
		}
		else {
			dst_fd = open(sd->d_name, O_WRONLY | O_CREAT | O_EXCL, 0666);

			while(read(src_fd,&ch,1))
			{
				write(dst_fd,&ch,1);
			}
			close(dst_fd);
			close(src_fd);
		}
	}
	dprintf(client_sock_fd, "HTTP/1.1 201 Created\r\nContent-Length: 0\r\n\r\n");
	closedir(dir);
	close(client_sock_fd);
	return;
}

void list(int client_sock_fd, struct ThreadBuffer* clients)
{
	int i;
	if(clients->tracker > 0){
		dprintf(client_sock_fd, "HTTP/1.1 200 Ok\r\nContent-Length: %d\r\n\r\n", clients->tracker*11);
		for(i = 0; i < clients->tracker; i++){
			char c_copy[100] = "";
			strcat(c_copy, clients->savedBackupNames[i].c_str());
			write(client_sock_fd, c_copy, 10);
			dprintf(client_sock_fd, "\n");
		}
	}
	else
	{
		dprintf(client_sock_fd, "HTTP/1.1 200 Ok\r\nContent-Length: 0\r\n\r\n");
	}
	//dprintf(client_sock_fd, "HTTP/1.1 200 Ok\r\nContent-Length: 0\r\n\r\n");
	close(client_sock_fd);
}

void recv_http_header(int client_sock_fd, struct httpObject* header) {
	// read our new socket file descriptor into the buffer
	int recv_header = recv(client_sock_fd, header->buffer, 4096, 0);
	if (recv_header == -1) {
		perror("recv() on header");
		exit(1);
	}
	// check if the whole header is in the buffer
	char const *endDelim = "\r\n\r\n";
	bool found = false;
	while (found == false) {
		char *endHeader = strstr(header->buffer, endDelim);
		if (endHeader == NULL) {
			memset(header->buffer, 0, sizeof(header->buffer));
			recv_header = recv(client_sock_fd, header->buffer, 4096, 0);
			if (recv_header == -1) {
				perror("recv() on header");
				exit(1);
			}
		} else {
			found = true;
		}
	}
	return;
}

void validate_http_header(int client_sock_fd, struct httpObject* header) {
	sscanf(header->buffer, "%s %s %s", header->request, header->slash_filename, header->protocol);
	header->filename = header->slash_filename + 1;
	// check if valid http version -  505
	if (strcmp(header->protocol, "HTTP/1.1") != 0) {
		dprintf(client_sock_fd, "HTTP/1.1 505 HTTP Version Not Supported\r\nContent-Length: 0\r\n\r\n");
		close(client_sock_fd);
		return;
	}
	bool r_slash = false;
	if(strstr(header->filename, "r/") != NULL) {
		r_slash = true;
	}
	// check if valid file name length - 400
	if (strlen(header->filename) != 10 && strcmp(header->filename, "b") != 0
	&& strcmp(header->filename, "r") != 0 && strcmp(header->filename, "l") != 0
	&& !r_slash) {
		dprintf(client_sock_fd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n");
		close(client_sock_fd);
		return;
	}

	if(!r_slash) {
		// check if valid file name  - 400
		for (char * i = header->filename; *i; i++) {
			if (!isalnum(*i)) {
				dprintf(client_sock_fd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n");
				close(client_sock_fd);
				return;
			}
		}
	}

	// check if PUT/GET request - 400
	int get_req = strcmp(header->request, "GET");
	int put_req = strcmp(header->request, "PUT");
	//printf("get req is %d\n", get_req);
	if(get_req == 0){
		if(strcmp(header->filename, "b") == 0)
		{
			//printf("Before backup\n");
			strcpy(header->request, "backup");
		}
		if(strcmp(header->filename, "r") == 0)
		{
			strcpy(header->request, "recover");

		}
		if(r_slash)
		{
			header->filename = header->filename + 2;
			printf("Recover: r/%s\n", header->filename);
			strcpy(header->request, "recover_timestamp");
		}
		if(strcmp(header->filename, "l") == 0)
		{
			strcpy(header->request, "list");
		}
	}
	// printf("request is %s\n", header->request);

	if ((get_req != 0) && (put_req != 0)) {
		dprintf(client_sock_fd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n");
		close(client_sock_fd);
		return;
	}
	if(put_req == 0) {
		dprintf(client_sock_fd, "HTTP/1.1 100 Continue\r\n\r\n");
	}
}

void do_put_req(int client_sock_fd, struct httpObject* header) {
	struct stat buf;
	int file_exist = stat(header->filename, &buf);
	char trash_conlen[100];
	char con_len[100];
	char const *needle = "Content-Length";
	// open the file for action
	int put_fd = open(header->filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (put_fd == -1) {
		// check if permissions to open file - 403
		dprintf(client_sock_fd, "HTTP/1.1 403 Forbidden\r\nContent-Length: 0\r\n\r\n");
		close(put_fd);
		close(client_sock_fd);
		return;
	}
	// extract the content length from the header
	char *token = strtok(header->buffer, "\r\n");
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
		close(put_fd);
		close(client_sock_fd);
		return;
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
		return;
	}
	printf("[PUT] Successful PUT\n");
	// all is good if we reached this point - 201 or 200
	if (file_exist == -1){
		dprintf(client_sock_fd, "HTTP/1.1 201 Created\r\nContent-Length: 0\r\n\r\n");
		close(put_fd);
		close(client_sock_fd);
		return;
	} else {
		dprintf(client_sock_fd, "HTTP/1.1 200 Ok\r\nContent-Length: 0\r\n\r\n");
		close(put_fd);
		close(client_sock_fd);
		return;
	}
}


void do_get_req(int client_sock_fd, struct httpObject* header) {
	char *check_token;
	check_token = strtok(header->buffer, "\r\n");
	char const *needle = "Content-Length";
	bool break_out = false;
	// check if GET request has a content length header - 400
	while ((check_token != NULL) & (break_out == false)) {
		char *found = strstr(check_token, needle);
		if (found != NULL) {
			break_out = true;
			dprintf(client_sock_fd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n");
			close(client_sock_fd);
			return;
		}
		check_token = strtok(NULL, "\r\n");
	}
	char get_buffer[4096];
	// open our file and check for the file size so we can include it in our content-length
	int f_desc = open(header->filename, O_RDONLY, S_IRWXU);
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
			return;
		} else {
			// otherwise you don't have permissions - respond 403
			dprintf(client_sock_fd, "HTTP/1.1 403 Forbidden\r\nContent-Length: %d\r\n\r\n", length);
			close(f_desc);
			close(client_sock_fd);
			return;
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
	// response for an empty file - 200
	if (length == 0) {
		dprintf(client_sock_fd, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n", length);
		write(client_sock_fd, get_buffer, 0);
	}
	// error reading file - 500
	if (bytes_read == -1) {
		dprintf(client_sock_fd, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: %d\r\n\r\n", length);
		close(f_desc);
		close(client_sock_fd);
		return;
	}
	close(f_desc);
	close(client_sock_fd);
	return;
}

int main(int argc, char *argv[]){

	// declare ip, port, serverAddress
	char const *hostname = argv[1];
	int port = 8080;
	struct sockaddr_in serverAddress;
	int addrLen = sizeof(serverAddress);
	memset(&serverAddress, 0, sizeof serverAddress);


	//error handling for user defined arguments (port and ip)
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
	/*
	Initialize our CircularBuffer struct and its variables, mutex, and condition variables, pointers to store teh thread
	Create user-specified number of threads
	*/
	// start of communication with the client
	struct ThreadBuffer* clients = (struct ThreadBuffer*)malloc(sizeof(struct ThreadBuffer));

	int fd;
	//used for opening a directory
	struct dirent *sd;
	//for checking if we're opening a directory
	struct stat statBuf;
	DIR *dir;
	//open server directory
	dir = opendir(".");
	// Add existing backup copies to our backup list
	while((sd = readdir(dir)) != NULL) {
		fd = open(sd->d_name, O_RDONLY);
		if (fstat(fd, &statBuf) != 0) {
			// printf("fstat() failed\n");
		}
		if(S_ISDIR(statBuf.st_mode)) {
			// printf("%s is a directory\n", sd->d_name);
			if(strstr(sd->d_name, "backup-") != NULL) {
				char* copy_name = sd->d_name + 7;
				printf("*Added backup-%s from server directory\n", copy_name);
				std::string str = (copy_name);
				clients->savedBackupNames.push_back(str);
				clients->tracker++;
			}
		}
		close(fd);
	}

	while(1) {
		printf("Dispatcher: Waiting for request\n");
		//printf("before accepting\n");
		int client_sock_fd = accept(server_sock_fd, (struct sockaddr*) &serverAddress, (socklen_t*)&addrLen);
		if (client_sock_fd < 0) {
			perror("accept()");
			exit(1);
		}
		struct httpObject header;

		recv_http_header(client_sock_fd, &header);
		validate_http_header(client_sock_fd, &header);

		if (strcmp(header.request, "backup") == 0) {
			printf("Entering backup function\n");
			createBackup(client_sock_fd, clients);
			printf("Backup complete\n");
		}

		if (strcmp(header.request, "recover") == 0) {
			printf("Entering recover function\n");
			char no_timestamp[100] = "-1";
			recover(client_sock_fd, clients, no_timestamp);
			printf("Recovered from latest backup\n");
		}

		if (strcmp(header.request, "recover_timestamp") == 0) {
			printf("Entering recover function\n");
			recover(client_sock_fd, clients, header.filename);
			printf("Recovered from backup-%s\n", header.filename);
		}

		if (strcmp(header.request, "list") == 0) {
			printf("Entering list function\n");
			list(client_sock_fd, clients);
			printf("Backup directories listed\n\n");
		}

		if (strcmp(header.request, "PUT") == 0) {
			printf("Entering PUT function\n");
			do_put_req(client_sock_fd, &header);
			printf("PUT request complete\n");
		}

		if (strcmp(header.request, "GET") == 0) {
			printf("Entering GET function\n");
			do_get_req(client_sock_fd, &header);
			printf("GET request complete\n");
		}
	}
}
