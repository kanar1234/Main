Alan Szeto, Diego Vasquez

This project is a multi-threaded HTTP server using sockets that supports GET and PUT requests to read and write files and stores them into the server.
An additional requirement is that this project creates backups of previous requests and these backups can be recovered by using the timestamp of previous requests.

Instructions:

Run the makefile
	- $ make

Run the server in one terminal - use sudo to avoid any permission errors
	- $ sudo ./httpserver ip port

Use curl commands in another terminal that are directed to the ip and port that are specified when you booted up the server.
