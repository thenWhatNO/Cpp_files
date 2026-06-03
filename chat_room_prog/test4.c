#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080

int main(){

	int server_fd, client_fd;
	struct sockaddr_in address;
	socklen_t addrlen = sizeof(address);
	char *msg = "hello";

	if(server_fd = socket(AF_INET, SOCK_STREAM, 0) < 0){
		perror("could not creat socket for server\n");
		return -1;
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0){
		perror("could not bind addres to server socket\n");
		close(server_fd);
		return -1;
	}

	if(listen(server_fd, 3) < 0){
		perror("could not listen\n");
		close(server_fd);
		return -1;
	}

	if((client_fd = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0){
		perror("can not accept\n");
		close(server_fd);
		return -1;
	}

	int byt_s = send(client_fd, msg, strlen(msg), 0);
	if(byt_s == -1){
		perror("cant sund msg\n");
		return -1;
	} else {
		printf("sent %d byts: %s\n", byt_s, msg);
	}

	close(client_fd);
	close(server_fd);
	return 0;

}
