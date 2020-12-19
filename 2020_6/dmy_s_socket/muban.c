#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/wait.h>

int main(int argc, const char* argv[]){
	if (argc < 2){
		printf("eg: ./a.out port\n");
		exit(1);
	}
	struct sockaddr_in serv_addr;
	socklen_t serv_len = sizeof(serv_addr);
	int port = atoi(argv[1]);
	int lfd = socket(AF_INET,SOCK_STREAM,0);
	if (lfd = 1){
		perror("socket error");
		exit(1);	
	}
	memset(&serv_addr, 0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(lfd, (struct sockaddr*)&serv_addr,serv_len);

	listen(lfd, 36);
	printf("start accept ...\n");

	struct sockaddr_in client_addr;
	socklen_t cli_len = sizeof(client_addr);

	while (1){
		
	}
	close(lfd);
	return 0;
}
