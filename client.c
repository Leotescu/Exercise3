#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include<arpa/inet.h>

#define SIZE_MSG 1024

char buffer1[1024];
char buffer[1024];

int main(int argc , char *argv[]){
	int clientSocket;
	
	char path[100];	
	
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	serverAddr.sin_family = AF_INET;

	serverAddr.sin_port = htons(atoi(argv[1]));

	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	addr_size = sizeof serverAddr;
	connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
	
	strncpy(buffer, argv[2], strlen(argv[2]));
	strncpy(buffer1, argv[3], strlen(argv[3]));
	send(clientSocket, buffer, SIZE_MSG, 0);  // filename
	send(clientSocket, buffer1, SIZE_MSG, 0);  // path

	recv(clientSocket, buffer, SIZE_MSG, 0);
	printf("%s\n", buffer);

	return 0;
}

