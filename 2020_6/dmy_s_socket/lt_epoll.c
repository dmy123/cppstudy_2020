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
#include <sys/epoll.h>

int main(int argc, const char* argv[]){
	if (argc < 2){
		printf("eg: ./a.out port\n");
		exit(1);
	}
	pid_t pid = fork();
	if (pid > 0){
		exit(1);	
	}
	setsid();
	umask(0);
	chdir(getenv("HOME"));
	struct sockaddr_in serv_addr;
	socklen_t serv_len = sizeof(serv_addr);
	int port = atoi(argv[1]);
	int lfd = socket(AF_INET,SOCK_STREAM,0);
	if (lfd == 1){
		perror("socket error");
		exit(1);	
	}
	memset(&serv_addr, 0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	printf("server ip: %s, port:%d\n",serv_addr.sin_addr.s_addr,serv_addr.sin_port);
	bind(lfd, (struct sockaddr*)&serv_addr,serv_len);

	listen(lfd, 36);
	printf("start accept ...\n");

	struct sockaddr_in client_addr;
	socklen_t cli_len = sizeof(client_addr);
	
	int epfd = epoll_create(3000);
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = lfd;
	epoll_ctl(epfd,	EPOLL_CTL_ADD,lfd,&ev);
	
	struct epoll_event all[2000];
	while (1){
		int ret = epoll_wait(epfd,all,sizeof(all) / sizeof(struct epoll_event),-1);
		printf("-------------------epoll wait----------------------\n");
		int i = 0;
		for (i = 0;i < ret;++i){
			int fd = all[i].data.fd;
			if (fd == lfd){
				int cfd = accept(lfd,(struct sockaddr*)&client_addr,&cli_len);
				if (cfd == -1){
					perror("accept error");
					exit(1);
				}
				struct epoll_event temp;
				temp.events = EPOLLIN;
				temp.data.fd = cfd;
				epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&temp);
				char  ip[64] = {0};
				printf("new client ip:%s,port:%d\n",
					inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,ip,sizeof(ip)),
					ntohs(client_addr.sin_port));
			}
			else{
				if (!all[i].events&EPOLLIN){
					continue;
				}
				char buf[5] = {0};
				int len = recv(fd,buf,sizeof(buf),0);
				if (len == -1){
					perror("recv error");
					exit(1);
				}
				else if (len == 0){
					printf("client disconnect ......\n");
					ret = epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
					if (ret == -1){
						perror("epoll_ctl - del error");
						exit(1);
					}
					close (fd);
				}
				else{
					printf("recv buf:%s\n",buf);
					write(fd,buf,len);
				}
			}
		}
	}
	close(lfd);
	return 0;
}
