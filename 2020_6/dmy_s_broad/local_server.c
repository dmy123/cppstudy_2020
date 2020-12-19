#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/un.h>

int main(int argc, const char* argv[]){
	pid_t pid = fork();
	if (pid > 0){
		exit(1);	
	}
	setsid();
	umask(0);
	chdir(getenv("HOME"));
	int lfd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if (lfd == -1){
		perror("socket error");
		exit(1);
	}
	unlink("server.socket");
	struct sockaddr_un serv;
	serv.sun_family = AF_LOCAL;
	strcpy(serv.sun_path,"server.socket");
	int ret = bind(lfd,(struct sockaddr*)&serv,sizeof(serv));
	if (ret == -1){
		perror("bind error");
		exit(1);
	}
	ret = listen(lfd, 36);
	if (ret == -1){
		perror("bind error");
		exit(1);
	}
	struct sockaddr_un client;
	socklen_t cli_len = sizeof(client);
	int cfd = accept(lfd,(struct sockaddr*)&client, &cli_len);
	if (cfd == -1){
		perror("accept error");
		exit(1);
	}
	printf("client bind-file: %s\n",client.sun_path);
	while (1){
		char buf[1024] = {0};
		int len = recv(cfd,buf,sizeof(buf),0);
		if (len == -1){
			perror("recv error");
			exit(1);
		}
		else if (len == 0){
			printf("client disconect ... \n");
			close(cfd);
			break;
		}
		else{
			printf("recv buf: %s\n");
			send(cfd,buf,len,0);
		}
	}
	close(cfd);
	close(lfd);	
	return 0;
}
