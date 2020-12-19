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

typedef struct SockInfo{
	int fd;
	struct sockaddr_in addr;
	pthread_t id;
}SockInfo;

void *worker(void* argv){
	char ip[64];
	char buf[1024];
	SockInfo* info = (SockInfo*) argv;
	while(1){
		printf("client ip: %s,port: %d\n",inet_ntop(AF_INET,
				&info->addr.sin_addr.s_addr,ip,sizeof(ip)),
				ntohs(info->addr.sin_port));
		int len = read(info->fd,buf,sizeof(buf));
		if (len == -1){
			perror("read error");
			pthread_exit(NULL);
		}
		else if (len == 0){
			printf("client close\n");
			close(info->fd);
			break;
		}
		else{
			printf("recv buf: %s\n", buf);
			write(info->fd, buf, len);
		}
	}
	return NULL;
}

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
	printf("lfd: %d\n",lfd);
	if (lfd == 1){
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

	socklen_t cli_len = sizeof(struct sockaddr_in);
	serv_addr.sin_family = AF_INET;

	SockInfo info[256];
	int i = 0;
	while (1){
		info[i].fd = accept(lfd,(struct sockaddr*)&info[i].addr,&cli_len);
		pthread_create(&info[i].id,NULL,worker,&info[i]);
		pthread_detach(info[i].id);
		++i;
		if (i == 256){
			break;
		}
	}
	close(lfd);
	pthread_exit(NULL);
	return 0;
}
