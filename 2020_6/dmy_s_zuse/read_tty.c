#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char* argv[]){
	int fd = open("/dev/tty",O_RDWR|O_NONBLOCK);
	
	int flags = fcntl(fd,F_GETFL);
	flags|= O_NONBLOCK;
	fcntl(fd, F_SETFL,flags);

	char buf[256];
	int ret = 0;
	while (1){
		ret = read(fd,buf,sizeof(buf));
		if (ret < 0)
		{
			perror("READ ERR:");
			printf("ret is %d\n", ret);
		}
		if (ret){
			printf("buf is %s\n",buf);
		}
		printf("haha\n");
		sleep(1);
	}
	close(fd);	
	return 0;
}
