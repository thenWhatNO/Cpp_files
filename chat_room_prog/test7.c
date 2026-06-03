#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/select.h>
#include <arpa/inet.h>

#define PORT 8080

int main(){
	struct addrinfo hint, *res;
	int serverfd;

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_flags = AI_PASSIVE;

	if(getaddrinfo("0.0.0.0", "8080", &hint, &res) == -1){perror("getaddrinfo fail\n"); return -1;}

	for(struct addrinfo *p = res; p != NULL; p = p->ai_next){
		if((serverfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){perror("socket fail\n"); continue;}
		if(bind(serverfd, p->ai_addr, p->ai_addrlen) == -1){close(serverfd); perror("bind fail\n"); continue;}
		if(listen(serverfd, 5) == -1){close(serverfd); perror("listen fail\n");continue;}
		break;
	}
	printf("server run on port 8080...\n");

	//technical stuff
	int run = 1;

	//set for the clients and there activity
	fd_set client_set;
	int n, index;
	n = index = 0;
	int sets[100] = {0};
	FD_ZERO(&client_set);
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);

	//set for the server to "hear" connection
	fd_set read_fds;

	while(run){

		FD_ZERO(&read_fds);
		FD_SET(serverfd, &read_fds);

		struct timeval tv = {1,0};
		int resl = select(serverfd+1, &read_fds, NULL, NULL, &tv);
		if(resl == 0){}
		else if(resl == -1){perror("conaction select fail\n"); continue;}
		else {
			int new_sock = accept(serverfd, (struct sockaddr*)&client_addr, &client_addr_len);
			if(new_sock != -1){
				sets[index] = new_sock;
				index++;
				n = new_sock +1;
				printf("found new conection\n");
			}
		}

		if(n == 0){continue;}

		for(int i = 0; i <= index; i++){
			FD_SET(sets[i], &client_set);
		}

		struct timeval tval = {1,0};
		int rest = select(n, &client_set, NULL, NULL, &tval);
		if(rest == -1){continue;}
		else if(rest == 0){continue;}

		char buff[1024];
		for(int i = 0; i <= index; i++){
			int client = sets[i];
			if(FD_ISSET(client, &client_set)){
				int get = recv(client, buff, sizeof(buff), 0);
				if(get == -1){continue;}
				else if(get == 0){
					printf("someone exit the server\n");
					FD_CLR(client, &client_set);
					for(int off = i; i < index-1; off++){
						sets[off] = sets[i+1];
					}
					index--;
					continue;
				}
				printf("get msg : %s\n", buff);
			}
		}

		for(int i = 0; i <= index; i++){
			send(sets[i], &buff, sizeof(buff), 0);
		}
		memset(buff, 0, sizeof(buff));
	}

	printf("exit server 8080\n");
	close(serverfd);
	freeaddrinfo(res);
}
