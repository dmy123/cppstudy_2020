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
	inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr.s_addr);
	
struct sockaddr_in client;
	socklen_t cli_len = sizeof(client);

	while (1){
		char buf[1024] = {0};
		fgets(buf, sizeof(buf),stdin);
		sendto(fd,buf,strlen(buf) + 1,0,(struct sockaddr*)&serv, sizeof(serv));
		recvfrom(fd,buf,sizeof(buf),0,NULL,NULL);
		printf("recv buf:%s\n",buf);

	}
	close(fd);
	return 0;
}
