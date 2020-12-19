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
	
	int maxfd = lfd;
	
	fd_set reads,temp;
	FD_ZERO(&reads);
	FD_SET(lfd,&reads);

	while (1){
		temp = reads;
		int ret = select(maxfd + 1, &temp,NULL, NULL,NULL);
		if (ret == -1){
			perror("select error");
			exit(1);
		}
		if (FD_ISSET(lfd,&temp)){
			int cfd = connect(lfd,&client_addr,cli_len);
			if (cfd == -1){
				perror("accept error");
				exit(1);
			}
			char ip[64];
			printf("new client ip:%s,port:%d\n",
				inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,ip,sizeof(ip)),
				ntohs(client_addr.sin_port));
			FD_SET(cfd,&reads);
			maxfd = cfd > maxfd?cfd:maxfd;		
		}
		for (int i = lfd + 1;i < maxfd + 1;++i){
			if (FD_ISSET(i, &temp)){
				char buf[1024] = {0};
				int len = recv(i, &buf,sizeof(buf), 0);
				if (len == -1){
					perror("rcev eror");
					exit(1);
				}
				else if (len == 0){
					printf("client close\n")
					close(i);
					FD_CLR(i, &read);
				}
				else{
					printf("recv buf : %s\n", buf);
					send(i,buf,strlen(buf) +1,0);
				}
			}
		}
	}
	close(lfd);
	return 0;
}
