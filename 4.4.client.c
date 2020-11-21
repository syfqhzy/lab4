#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <unistd.h>

void func(int socket_desc) 
{ 
	char buff[80]; 
	int n; 
	for (;;)
        { 
		bzero(buff, sizeof(buff)); 
		printf("Enter any message : "); 
		n = 0; 
		while ((buff[n++] = getchar()) != '\n'); 
		write(socket_desc, buff, sizeof(buff)); 
		bzero(buff, sizeof(buff)); 
		read(socket_desc, buff, sizeof(buff)); 
		printf("From Server : %s", buff); 
		if ((strncmp(buff, "exit", 4)) == 0)
                { 
			printf("Client Exit...\n"); 
			break; 
		} 
	} 
} 

int main() 
{ 
	int socket_desc, connfd; 
	struct sockaddr_in server, client; 

	// socket create and varification 
	socket_desc = socket(AF_INET, SOCK_STREAM, 0); 
	if (socket_desc == -1) { 
		printf("Could not create socket...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&server, sizeof(server)); 

	// assign IP, PORT 
	server.sin_family = AF_INET; 
	server.sin_addr.s_addr = inet_addr("192.168.1.109"); 
	server.sin_port = htons(8888); 

	// connect the client socket to server socket 
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) != 0)
        { 
		printf("connection with the server failed...\n"); 
		exit(0); 
	} 
	else
		printf("connected to the server..\n"); 

	// function for chat 
	func(socket_desc); 

	// close the socket 
	close(socket_desc); 
} 

