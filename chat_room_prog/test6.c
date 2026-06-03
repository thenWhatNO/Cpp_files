#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

#define PORT 8080


int main(){
	struct addrinfo hint, *res;
	int socketfd;

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;

	if (getaddrinfo("0.0.0.0", "8080", &hint, &res) == -1){
		perror("no addrinfo");
		return 0;
	}

	socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if(connect(socketfd, res->ai_addr, res->ai_addrlen) == -1){
		perror("cant connect\n");
	}

	printf("you enter server at port 8080, u can send msg with a len of 1000 char\n\n");

	int run = 1;
	char buff[1000] = "hello world";
	while(run){
		fd_set readfd;
		FD_ZERO(&readfd);
		FD_SET(socketfd, &readfd);

		struct timeval tv = {2,0};

		int rtn = select(socketfd+1, &readfd, NULL, NULL, &tv);
		if(rtn == -1){perror("cant recv msg\n");}
		else if(rtn == 0){}
		else {
			char buff[1024];
			if(FD_ISSET(socketfd, &readfd)){
				recv(socketfd, buff, sizeof(buff), 0);
				printf("%s\n", buff);
			}
		}

		char msg[1000];
		int c, i;
		for(i = 0; (c = getchar()) != '\n'; i++){
			msg[i] = c;
		}
		msg[i] = '\0';

		if(msg[0] == '\n'){run = 0;}

		if(send(socketfd, msg, sizeof(msg), MSG_OOB) == -1){
			perror("cant send msg\n");
		}
	}
	freeaddrinfo(res);
	close(socketfd);
}
