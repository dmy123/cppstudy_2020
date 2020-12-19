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
	int fd = socket(AF_LOCAL,SOCK_STREAM,0);
	if (fd == -1){
		perror("socket error");
		exit(1);
	}
	unlink("client.socket");
	struct sockaddr_un client;
	client.sun_family = AF_LOCAL;
	strcpy(client.sun_path, "client.socket");
	int ret = bind(fd,(struct sockaddr*)&client,sizeof(client));
	if (ret == -1){	
		perror("bind error");
		exit(1);
	}

	struct sockaddr_un serv;
	serv.sun_family = AF_LOCAL;
	strcpy(serv.sun_path,"serv.socket");
	connect(fd,(struct sockaddr*)&serv,sizeof(serv));

	while (1){
		char buf[1024] = {0};
		fgets(buf,sizeof(buf),stdin);
		send(fd,buf,strlen(buf) + 1,0);
		
		char recv_buf[1024];
		recv(fd,recv_buf,sizeof(recv_buf),0);
		printf("client:recv buf:%s\n",buf);
	}
	close(fd);
	return 0;
}
