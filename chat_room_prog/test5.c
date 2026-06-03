#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/select.h>

#define CHAT_HTML "chat.html"

typedef struct {
	char *ip;
	char *port;
	char *msg;
} Post;

typedef struct {
	Post *posts;
} Post_store;


typedef struct {
	int socket;
	struct sockaddr adders;
} client;

typedef struct {
	int size;
	int cap;
	int *clients_fd;
} clients;



void read_file(char **buff, char *file){
	FILE *ptr = fopen(file, "r");

	fseek(ptr, 0, SEEK_END); //move the corser to the target point (to the end of the file)
	long fil_len = ftell(ptr); // count the corrent position of the corser from the start (0)
	rewind(ptr); // move the corsesd back to the start of the file

	*buff = realloc(*buff, fil_len+1);

	size_t file_len = fread(*buff, 1, fil_len, ptr); // read the file at once to the size
	(*buff)[file_len] = '\0';

	fclose(ptr);
}

void creat_client_socks(clients *cs){
	cs->size = 0;
	cs->cap = 2;
	cs->clients_fd = malloc(sizeof(int)*cs->cap);
}

void add_new_client(clients *cs, int sock){
	if(cs->size >= cs->cap){
		cs->cap *= 2;
		cs->clients_fd = realloc(cs->clients_fd, sizeof(int)*cs->cap);
	}
	cs->clients_fd[cs->size] = sock;
	cs->size++;
}

void remove_client(clients *cs, int sock){
	int idx, del;
	for(int i = 0; i < cs->size; i++){
		if(sock == cs->clients_fd[i]){
			del = 1;
			cs->clients_fd[i] = 0;
			cs->size--;
		}
		if(del){
			cs->clients_fd[i] = cs->clients_fd[i+1];
		}
	}
}

void free_client_socks(clients *cs){
	free(cs->clients_fd);
}

int main(){
	struct addrinfo hint, *res;
	char ip_str[INET6_ADDRSTRLEN];

	clients clients_sock;
	creat_client_socks(&clients_sock);

	int server_sockfd;

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_flags = AI_PASSIVE;

	if((getaddrinfo(NULL, "8080", &hint, &res)) < 0){
		perror("could not find addr info\n");
		return -1;
	}

	for(struct addrinfo *p = res; p != NULL; p = p->ai_next){
		void *adr;
		char *ip_ver;
		in_port_t port;

		if(p->ai_family == AF_INET){
			struct sockaddr_in *ip4 = (struct sockaddr_in*)p->ai_addr;
			adr = &(ip4->sin_addr.s_addr);
			port = ntohs(ip4->sin_port);
			ip_ver = "IPv4";
		} else if (p->ai_family == AF_INET6) {
			struct sockaddr_in6 *ip6 = (struct sockaddr_in6*)p->ai_addr;
			adr = &(ip6->sin6_addr.s6_addr);
			port = ntohs(ip6->sin6_port);
			ip_ver = "IPv6";
		}

		if((server_sockfd = socket(p->ai_family, SOCK_STREAM, 0)) == -1){
			perror("could not creat socket");
			continue;
		}

		if(bind(server_sockfd, p->ai_addr, p->ai_addrlen) == -1){
			close(server_sockfd);
			perror("can not bind server to addr");
			continue;
		}

		inet_ntop(p->ai_family, adr, ip_str, sizeof(ip_str));
		printf("creat and bind sockt with ip %s : %s (%d)\n", ip_ver, ip_str, port);

		break;
	}

	if(listen(server_sockfd, 5) == -1){
		close(server_sockfd);
		perror("can not listen sserer\n");
		return -1;
	}

	int run = 1;

	int client_sockfd;
	struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);

	fd_set clients_set;
	int n = 0;
	FD_ZERO(&clients_set);

	while(run){

		fd_set read_fds;
		struct timeval tv0 = {1, 0};
		FD_ZERO(&read_fds);

		FD_SET(server_sockfd, &read_fds);

		int to = select(server_sockfd+1, &read_fds, NULL, NULL, &tv0);

		if(to == 0){}
		else if(to == -1){perror("error at select accation\n");}
		else{
			int new_sock = accept(server_sockfd, (struct sockaddr*)&client_addr, &addr_len);
			if(new_sock != -1){
				add_new_client(&clients_sock, new_sock);
				char client_ip[INET_ADDRSTRLEN];
				inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
				int client_port = ntohs(client_addr.sin_port);
				printf("acept client at : %s [%d]\n", client_ip, client_port);
				FD_SET(clients_sock.clients_fd[clients_sock.size-1], &clients_set);
				n = clients_sock.clients_fd[clients_sock.size-1] +1;
			}
		}

		if(n == 0) continue;

		struct timeval tv;
		fd_set fs= clients_set;
		tv.tv_sec = 1;

		int rv = select(n, &fs, NULL, NULL, &tv);

		if(rv == -1){
			perror("select error\n");
			continue;
		} else if (rv == 0){
			continue;
		}


		char buff[1024] = {0};
		int sndr = 0;
		for(int i = 0; i < clients_sock.size; i++){
			int rev = recv(clients_sock.clients_fd[i], buff, sizeof(buff), 0);
			if(rev == -1){continue;}
			else if (rev == 0){
				printf("client exit server\n");
				FD_CLR(clients_sock.clients_fd[i], &clients_set);
				remove_client(&clients_sock, clients_sock.clients_fd[i]);
				continue;
			}
			sndr = clients_sock.clients_fd[i];
			printf("%s\n", buff);

			for(int i = 0; i < clients_sock.size; i++){
			send(clients_sock.clients_fd[i], &buff, sizeof(buff), 0);
			}
		}
	}

	printf("server stoped\n");
	close(server_sockfd);
	freeaddrinfo(res);
}
