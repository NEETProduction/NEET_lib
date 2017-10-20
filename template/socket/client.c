#define _POSIX_C_SOURCE 200112L
#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define bool int
#define false 0
#define true 1

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		fprintf(stderr, "Usage : %s [server_address] [server_port]\n", argv[0]);
		return 1;
	}
	
	int socket_fd;

	#ifdef OLD_FASHION
	char *host_address = argv[1];
	int portno = atoi(argv[2]);

	struct sockaddr_in address_package = {	.sin_family = AF_INET,
						.sin_port = htons(portno),
						.sin_addr.s_addr = inet_addr(host_address)};
	socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

	connect(socket_fd, (struct sockaddr*)&address_package, sizeof(struct sockaddr_in));

	#else
	char *host_address = argv[1];
	char *portno_str = argv[2];

	struct addrinfo hints = {	.ai_family = AF_INET,
					.ai_socktype = SOCK_STREAM,
					.ai_flags = 0,
					.ai_protocol = IPPROTO_IP};

	struct addrinfo *addr_package;

	if(getaddrinfo(host_address, portno_str, &hints, &addr_package))
	{
		perror("Error getaddrinfo()\n");
		return 1;
	}

	struct addrinfo *rp;
	for(rp = addr_package ; rp ; rp = rp -> ai_next)
	{
		if((socket_fd = socket(rp -> ai_family, rp -> ai_socktype, rp -> ai_protocol)) < 0)
		{
			continue;
		}

		if(!connect(socket_fd, rp -> ai_addr, rp -> ai_addrlen))	//success
		{
			break;
		}

		close(socket_fd);
	}

	if(!rp)
	{
		perror("Failed to connect()\n");
		return 1;
	}

	freeaddrinfo(addr_package);
	#endif

	printf("Connection Estabilished(client)\n");

	char *buf = NULL;
	size_t rd_size = 0;
	bool termination = false;

	do
	{
		putchar('>');
		fflush(stdout);
		
		if(getline(&buf, &rd_size, stdin) < 0)
		{
			goto free_resource;
		}
		size_t msg_length = strlen(buf);
		buf[--msg_length] = 0;
		
		printf("Read size : %lu, strlen : %lu\n", rd_size, msg_length);


		send(socket_fd, &msg_length, sizeof(size_t), 0);	//send size of target string first
		send(socket_fd, buf, msg_length, 0);

		if(!strcmp(buf, "!q"))
		{
			termination = true;
		}

		free_resource:
		free(buf);
		buf = NULL;
	}
	while(!termination);


	close(socket_fd);
	return 0;
}
