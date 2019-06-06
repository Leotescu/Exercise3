#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc , char *argv[]){
	int clientSocket;
	char buffer[1024];
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
	send(clientSocket, buffer, sizeof(buffer), 0);	
	recv(clientSocket, buffer, sizeof(buffer), 0);
	printf("Data received: %s\n",buffer);


	/*recv(clientSocket, buffer, strlen(buffer), 0);
	printf("Data received: %s",buffer);
	
	while(1){
		   
		fgets(buffer, sizeof(buffer), stdin);
		if(send(clientSocket, buffer, sizeof(buffer), 0)){
		recv(clientSocket, buffer, sizeof(buffer), 0);
		printf("Data received: %s",buffer);
		}
	}*/
	return 0;
}

