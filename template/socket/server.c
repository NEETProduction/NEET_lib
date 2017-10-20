/*
Copyright 2017 Jeonghun Gong

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

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

	if(argc != 2)
	{
		fprintf(stderr, "Usage : %s [portno]\n", argv[0]);
		return 1;
	}
	
	int socket_fd;
	
	#ifdef OLD_FASHION
	int portno = atoi(argv[1]);
	
	struct sockaddr_in address_package = {	.sin_family = AF_INET,		//use IPv4
						.sin_port = htons(portno),	//port number : portno
						.sin_addr.s_addr = INADDR_ANY};	//acepts all addresses
	socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

	bind(socket_fd, (struct sockaddr*)&address_package, sizeof(struct sockaddr_in));	

	#else	//new way

	char *portno_str = argv[1];	
	struct addrinfo hints = {	.ai_family = AF_INET,		//IPv4 only
					.ai_socktype = SOCK_STREAM,	//use TCP
					.ai_flags = AI_PASSIVE,
					.ai_protocol = IPPROTO_IP,	//put zero for all possible protocol
					.ai_canonname = NULL,
					.ai_addr = NULL,
					.ai_next = NULL};

	struct addrinfo *addr_package;

	if(getaddrinfo(NULL, portno_str, &hints, &addr_package))
	{
		perror("Error getaddrinfo()\n");
		return 1;
	}

	//it returns list of address structure
	struct addrinfo *rp;
	for(rp = addr_package ; rp ; rp = rp -> ai_next)
	{
		if((socket_fd = socket(rp -> ai_family, rp -> ai_socktype, rp -> ai_protocol)) < 0)
		{
			continue;
		}

		if(!bind(socket_fd, rp -> ai_addr, rp -> ai_addrlen))	//success
		{
			break;
		}

		close(socket_fd);
	}

	freeaddrinfo(addr_package);
	if(!rp)
	{
		//Failed to bind
		return 1;
	}
	#endif

	if(listen(socket_fd, 500))
	{
		perror("Failed to listen()\n");
		return 1;
	}
	
	//Accept side-
	struct sockaddr peer_addr;
	socklen_t peer_addr_len;
	getsockname(socket_fd, &peer_addr, &peer_addr_len);	//update values
	
	int client_fd = accept(socket_fd, (struct sockaddr*)&peer_addr, &peer_addr_len);
	if(client_fd < 0)
	{
		perror("Failed to accept()\n");
		return 1;
	}

	printf("Connection Estabilished(server)\n");

	while(1)
	{
		size_t rd_size;
		char *buf;

		if(recv(client_fd, &rd_size, sizeof(size_t), 0) <= 0)
		{
			perror("Disconnected or Error\n");
			break;
		}
		
		printf("Size : %lu\n", rd_size);
		buf = (char*)malloc(rd_size);
		
		if(recv(client_fd, buf, rd_size, 0) <= 0)
		{
			//error
			break;
		}

		printf("Message : %s\n", buf);
		free(buf);
	}

	close(socket_fd);


	return 0;
}
