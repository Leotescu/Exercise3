#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include<arpa/inet.h>

#define SIZE_MSG 1024

char commands[100];

int main(int argc , char *argv[]){
	int welcomeSocket, newSocket;
	char path_recv[1024];
	char file[100];

	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;

	welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

	serverAddr.sin_family = AF_INET;

	serverAddr.sin_port = htons(atoi(argv[1]));

	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

	if(listen(welcomeSocket,100)==0)
		printf("Hello\n");
	else
		printf("Error\n");
	while(1){
	addr_size = sizeof serverStorage;
	newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
	
	recv(newSocket, file, SIZE_MSG, 0); 
	printf("Required file: %s\n",file); 
	recv(newSocket, path_recv, SIZE_MSG, 0);
	printf("The path: %s\n",path_recv);
	
	strncpy(commands, "cp ", strlen("cp "));
	strcpy(commands + 3, commands + strlen(commands));
	strncat(commands, argv[2], strlen(argv[2]));
	strncat(commands, file, strlen(file));
	strncat(commands, " ", 1);
	strncat(commands, path_recv, strlen(path_recv));
	if(system(commands) == 0)
		send(newSocket, file, SIZE_MSG, 0);
	else
		send(newSocket, "File no found",13,0);
	
	commands[0] = '\0';
	}
	
	return 0;
}
