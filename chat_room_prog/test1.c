#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORT 9091
#define BUFFER_SIZE 1024

int main(){
	int serverSock;
	if((serverSock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("could not get server");
		return -1;
	}

	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(PORT);

	if(bind(serverSock, (struct sockaddr*) &serverAddr, sizeof serverAddr) < 0){
		perror("could not bind socket");
		return -1;
	}

	if(listen(serverSock, 5) < 0){
		perror("could not listin");
		return -1;
	}

	printf("listening port %d\n", PORT);

	int run = 1;
	while(run){
		struct sockaddr_in clientAddr;
		socklen_t clientLen = sizeof clientAddr;
		int *clientSocket = malloc(sizeof(int));

		if((*clientSocket = accept(serverSock, (struct sockaddr *)&clientAddr, &clientLen)) < 0){
			perror("could not accept client");
			continue;
		}
		printf("client conected !\n");

		char *msg = "hello client :)";
		int len, byts_send;
		len = strlen(msg);
		if((send(*clientSocket, msg, len, 0)) == -1){
			perror("canot send msg\n");
			continue;
		} else {
			printf("sent %d bytes: %s\n", byts_send, msg);
		}

		close(*clientSocket);
	 	printf("bay client\n");
		free(clientSocket);

		printf("type x to stop/ or enter to continue");
		if(getchar() == 'x'){run = 0;}
	}

	close(serverSock);
	printf("server close");

	return 0;
}
