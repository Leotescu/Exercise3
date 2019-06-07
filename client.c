#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>



int main(int argc , char *argv[]){
	int clientSocket;
	char buffer[1024];
	char path[100];	
	char buffer1[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	serverAddr.sin_family = AF_INET;

	serverAddr.sin_port = htons(atoi(argv[1]));

	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	addr_size = sizeof serverAddr;
	connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
	
	strcpy(buffer, argv[2]);
	strcpy(buffer1, argv[3]);
	send(clientSocket, buffer, 1024, 0);  // filename
	send(clientSocket, buffer1, 1024, 0);  // path

	recv(clientSocket, buffer, 1024, 0);
	printf("%s\n", buffer);

	return 0;
}

