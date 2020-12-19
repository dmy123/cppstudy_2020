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
	pid_t pid = fork();
	if (pid > 0){
		exit(1);	
	}
	setsid();
	umask(0);
	chdir(getenv("HOME"));
	struct sockaddr_in serv_addr;
	socklen_t serv_len = sizeof(serv_addr);
	int port = 8787;
	int fd = socket(AF_INET,SOCK_DGRAM,0);
	if (fd == 1){
		perror("socket error");
		exit(1);	
	}
	memset(&serv_addr, 0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(fd, (struct sockaddr*)&serv_addr,serv_len);

	if (ret == -1){
		perror("bind error");
		exit(1);
	}

	struct sockaddr_in client;
	memset(&client,0,sizeof(client));
	client.sin_family = AF_INET;
	client.sin_port = htons(6767);
	inet_pton(AF_INET,"192.168.0.255",&client.sin_addr.s_addr);

	int flag = 1;
	setsockopt(fd,SOL_SOCKET,SO_BROADCAST,&flag,sizeof(flag));

	while (1){
		static int num = 0;
		char buf[1024] = {0};
		sprintf(buf,"hello ,udp = %d\n",num++);
		int ret = sendto(fd,buf,strlen(buf)+ 1,0,(struct sockaddr*)&client,sizeof(client));
		if (ret == -1){
			perror("sendto error");
			break;
		}
		printf("server == send buf: %s\n",buf);
		sleep(1);
	}
	close(fd);
	return 0;
}
