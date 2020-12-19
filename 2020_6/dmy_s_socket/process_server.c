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

void recycle(int num){
	pid_t pid;
	while (pid = waitpid(-1, NULL, 	WNOHANG) > 0){
		printf("child died, pid = %d\n",pid);
	}
}

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

	struct sigaction act;
	act.sa_handler = recycle;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGCHLD,&act,NULL);	
	struct sockaddr_in client_addr;
	socklen_t cli_len = sizeof(client_addr);
	serv_addr.sin_family = AF_INET;
	

	while (1){
		int cfd = accept(lfd,(struct sockaddr*)&client_addr,&cli_len);
		if (cfd == -1){	
			printf("accept error");
			exit(1);
		}
		printf("connect successful\n");
		pid_t pid = fork();
		if (pid == 0){
			close(lfd);
			char ip[64];
			while (1){
				printf("client ip:%s,port:%d\n",
				inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,ip,sizeof(ip)),
				ntohs(client_addr.sin_port));
				char buf[1024];
				int len = read(cfd,buf, sizeof(buf));			
				if (len == -1){
					perror("read error");
					exit(1);
				}
				else if (len == 0){
					printf("client close\n");
					close(cfd);
					break;
				}
				else{
					printf("recv buf %s\n", buf);
					write(cfd, buf,len);
				}
			}
			return 0;
		}
		else if (pid > 0){
			close(cfd);
		}	
	}
	close(lfd);
	return 0;
}
