#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>

int main(int argc,const char* argv[]){
	int fd = socket(AF_INET,SOCK_DGRAM,0);
	if (fd == -1){
		perror("sock error");
		exit(1);
	}
	struct sockaddr_in serv;
	memset(&serv,0,sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8765);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	int ret = bind(fd,(struct sockaddr*)&serv,sizeof(serv));
	if (ret == -1){
		perror("bind error");
		exit(1);
	}

	struct sockaddr_in client;
	socklen_t cli_len = sizeof(client);

	char buf[1024] = {0};
	while (1){
		int rcvlen = recvfrom(fd,buf,sizeof(buf),0,(struct sockaddr*)&client,&cli_len);
		if (rcvlen == -1){
			perror("recvfrom error");
			exit(1);
		}
		printf("recv buf:%s\n",buf);
		char ip[64] = {0};
		printf("client ip:%s,port:%d\n",
				inet_ntop(AF_INET,&client.sin_addr.s_addr,ip,sizeof(ip)),
				ntohs(client.sin_port));

		sendto(fd,buf,strlen(buf) + 1,0,(struct sockaddr*)&client,cli_len);
	}
	close(fd);
	return 0;
}
