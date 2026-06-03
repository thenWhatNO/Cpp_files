#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){


	// creat a struct fof holding the mask(hints) of wanted addr info
	/* and also creat a struct for the colaction of the
	   result we get from the itirastion*/
	struct addrinfo hints, *res;

	// creat a string with size that can hold ip addrese. to save the ip str
	char ip_str[INET6_ADDRSTRLEN];

	//allocat memory for the hints struct
	memset(&hints, 0, sizeof(hints));
	//set hints.ai_family to (any ip verstion) so it can look for ip4 and ip6
	hints.ai_family = PF_UNSPEC;
	//set hints.ai_socktype to look for stream (TCP) internet protacol
	hints.ai_socktype = SOCK_STREAM;

	/*this if trys to read the info from the addr "google.com",
	  in port "http" (the "server" port),
	  using the hints filtrasion,
	  and store the results in res,
	  if the getaddrinfo cant read anything it return -0 and get error*/
	if(getaddrinfo("google.com", "http", &hints, &res) < 0){
		perror("could not read addr\n");
		return 0;
	}

	/*this foor loop check for the results (copy to *p)
	  (p!=NULL) run the loop intul the p pointer well be NULL
	  p->ai_next, rewrite the *p to the next addrinfo*/
	for(struct addrinfo *p = res; p != NULL; p = p->ai_next){
		// creat an addr pointer; use void as uneversal parameter type
		void *addr;
		// creat a string pointer to store the ip version.
		const char *ip_version;

		// check if the p->ai_family is ipv4, if not jump to else block
		if(p->ai_family == AF_INET){
			//creat a struct that store the addr info of a spetific ip (ipv4)
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
			//take the ip addr from the struct sockaddr_in
			addr = &(ipv4->sin_addr);
			//init ip_version as ipv4
			ip_version = "IPv4";
		} else {
			//creat a struct to save the addr info of the ip
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
			//save the ip
			addr = &(ipv6->sin6_addr);
			ip_version = "IPv6";
		}

		//convert the addr param into a readable string
		inet_ntop(p->ai_family, addr, ip_str, sizeof(ip_str));
		printf("IP : %s [%s]\n", ip_version, ip_str);

		if (p == res){

			int sockfd;
			if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0){
				perror("no socket");
				continue;
			}

			if(connect(sockfd, p->ai_addr, p->ai_addrlen) < 0){
				perror("no connect");
				close(sockfd);
				continue;
			}

			printf("connect ip : %s", ip_str);

			const char *req =
				"GET / HTTP/ 1.1\r\n"
				"Host: www.google.com\r\n"
				"Connection: close\r\n"
				"User-Agent: MySimpleClient/1.0\r\n"
				"\r\n";
			if(send(sockfd, req, strlen(req), 0) < 0){
				perror("no send");
				close(sockfd);
				continue;
			}
			printf("sund request");

			char buff[1024];
			ssize_t byte_res;
			while((byte_res = recv(sockfd, buff, sizeof(buff)-1, 0)) > 0){
				buff[byte_res] = '\0';
				printf("get %.*s\n", (int)byte_res, buff);
			}

			close(sockfd);
			printf("\n\n%s\n", buff);
		}
	}

	//free the memory from addrinfo struct
	freeaddrinfo(res);

}

