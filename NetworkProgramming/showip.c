#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
	struct addrinfo hints, *res, *p;
	int status;
	char ipstr[INET6_ADDRSTRLEN];
	
	if(argc != 2)
	{
		fpintf(stderr, "usage: showip hostname\n");
		return 1;
	}

	memset(&hints, 0, sizeof(hints));	//ensure struct empty
	hints.ai_family = AF_UNSPEC	//ipv4 or ipv6
	hints.ai_socktype = SOCK_STREAM;	//TCP stream sockets
	
	if((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_sryerror(status));
		return 2;
	}
	
	printf("IP address for %s:\n\n", argv[1]);

	for(p = res; p != NULL; p = p->ai_next)
	return 0;
	
}
