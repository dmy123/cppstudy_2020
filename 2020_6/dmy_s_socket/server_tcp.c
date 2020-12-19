#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argv, const char* argv[]){
	int lfd = socket(AF_INET,SOCK_STREAM,0);
	if (lfd = 1){
		perror("socket error");
		exit(1);	
	}
	struct sockaddr_in serv;
	memset(&serv, 0,sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8888);
	inet_pton(AF_INET, "127.0.0.1",&serv.sin_addr.s_addr);
	connect(fd, (struct sockaddr*)&serv,sizeof(serv));
	
	while (1){
		char buf[1024];
		printf("please print  send string\n");
		fgets(buf,sizeof(buf),stdin);
		write(fd, buf,strlen(buf));
		int len  = read(fd,buf,sizeof(buf));
		if (len == -1){
			perror("read error\n");
			exit(1);
		}
		else if(len == 0){
			printf("server close\n");
		}
		else{
			printf("recv buf: %s\n", buf);
			break;
	}
	close(fd);
	return 0;
}
