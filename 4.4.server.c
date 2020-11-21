#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>

// Function designed for chat between client and server. 
void func(int socket_desc) 
{ 
	char buff[80]; 
	int n; 
	// infinite loop for chat 
	for (;;)
        { 
		bzero(buff, 80); 

		// read the message from client and copy it in buffer 
		read(socket_desc, buff, sizeof(buff)); 
		// print buffer which contains the client contents 
		printf("From client: %s\t To client : ", buff); 
		bzero(buff, 80); 
		n = 0; 
		// copy server message in the buffer 
		while ((buff[n++] = getchar()) != '\n') 
			; 

		// and send that buffer to client 
		write(socket_desc, buff, sizeof(buff)); 

		// if msg contains "Exit" then server exit and chat ended. 
		if (strncmp("exit", buff, 4) == 0) { 
			printf("Server Exit...\n"); 
			break; 
		} 
	} 
} 

// Driver function 
int main(int argc , char *argv[]) 
{ 
	int socket_desc, connfd, len; 
	struct sockaddr_in server, client; 

	// socket create and verification 
	socket_desc = socket(AF_INET, SOCK_STREAM, 0); 
	if (socket_desc == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&server, sizeof(server)); 

	// assign IP, PORT 
	server.sin_family = AF_INET; 
	server.sin_addr.s_addr = htonl(INADDR_ANY); 
	server.sin_port = htons(8888); 

	// Binding newly created socket to given IP and verification 
	if ((bind(socket_desc, (struct sockaddr *)&server , sizeof(server))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 

	// Now server is ready to listen and verification 
	if ((listen(socket_desc, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
	len = sizeof(client); 

	// Accept the data packet from client and verification 
	connfd = accept(socket_desc, (struct sockaddr *)&client, &len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	else
		printf("server acccept the client...\n"); 

	// Function for chatting between client and server 
	func(connfd); 

	// After chatting close the socket 
	close(socket_desc); 
} 

