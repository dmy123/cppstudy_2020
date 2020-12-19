#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, const char* argv[]){
	if (argc < 2){
		printf("eg: ./a.out port\n");
		exit(1);	
	}
	int port = atoi(argv[1]);
	int fd = socket(AF_INET, SOCK_STREAM,0);
	struct sockaddr_in serv;
	memset(&serv, 0,sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(port);
	inet_pton(AF_INET, "127.0.0.1",&serv.sin_addr.s_addr);
	connect(fd, (struct sockaddr*)&serv,sizeof(serv));
	
	while (1){
		char buf[1024];
		printf("client: please print  send string\n");
		fgets(buf,sizeof(buf),stdin);
		write(fd, buf,strlen(buf));
		char rbuf[1024];
		int len  = read(fd,rbuf,sizeof(buf));
		if (len == -1){
			perror("client:read error\n");
			exit(1);
		}
		else if(len == 0){
			printf("client:server close\n");
		}
		else{
			printf("client:recv buf: %s\n", rbuf);
			continue;
			//break;
		}
	}
	close(fd);
	return 0;
}
