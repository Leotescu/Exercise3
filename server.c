#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc , char *argv[]){
	int welcomeSocket, newSocket;
	char buffer[1024];
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
		printf("Listening\n");
	else
		printf("Error\n");

	addr_size = sizeof serverStorage;
	newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
	recv(newSocket, buffer, sizeof(buffer), 0);
	printf("Data received: %s\n",buffer);
	char s[100];
	strcpy(s, "ls /home/vlad/Desktop/ex/ex3/server_file | find ");
	strcat(s, buffer);
	system(s);
	send(newSocket,buffer,sizeof(buffer),0);

	/*fgets(buffer, sizeof(buffer), stdin);
	send(newSocket,buffer,strlen(buffer),0);

	while(1){
		
		if(recv(newSocket, buffer, sizeof(buffer), 0)){
		printf("Data received: %s",buffer); 
		if(strncmp(buffer, "exit", strlen(buffer)) == 0)
			return 1; 
		fgets(buffer, sizeof(buffer), stdin);
		send(newSocket,buffer,sizeof(buffer),0);
		}
	} */
	return 0;
}
