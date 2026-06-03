#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <termios.h>

int main(){
	struct addrinfo hint, *res;
	int socketfd;

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;

	if(getaddrinfo("0.0.0.0", "8080", &hint, &res) == -1){perror("getaddrinfo fail\n"); return -1;}
	if((socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){perror("socket fail\n"); return -1;}
	if(connect(socketfd, res->ai_addr, res->ai_addrlen) == -1){close(socketfd); perror("connect fail\n");return -1;}

	int run = 1;
	char buff[1000];

	fd_set read_sock;

	while(run){
		FD_ZERO(&read_sock);
		FD_SET(STDIN_FILENO, &read_sock);
		FD_SET(socketfd, &read_sock);

		struct timeval tv = {0, 100000};

		int slct = select(FD_SETSIZE, &read_sock, NULL, NULL, &tv);
		if(slct == -1){perror("select fail\n");continue;}
		else if(slct == 0){continue;}

		if(FD_ISSET(socketfd, &read_sock)){
			recv(socketfd, buff, sizeof(buff), 0);
			printf("%s", buff);
		}

		if(FD_ISSET(STDIN_FILENO, &read_sock)){
			char msg[1000];
			fgets(msg, sizeof(msg), stdin);
			printf("\x1b[1F");
			printf("\x1b[2K");
			if(send(socketfd, msg, sizeof(msg), MSG_OOB) == -1){perror("send fail\n");}
		}
	}
	freeaddrinfo(res);
	close(socketfd);
}
