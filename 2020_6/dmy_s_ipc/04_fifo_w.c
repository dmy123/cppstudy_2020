#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc,char* argv[]){
	if (argc != 2)
	{
		printf("./a.out filename\n");
		return -1;
	}
	int fd = open(argv[1],O_RDWR);
	printf("open ok");
	char buf[256];
	int num = 1;
	while (1){
		memset(buf,0x00,sizeof(buf));
		sprintf(buf,"xiaoming%04d",num++);
		write(fd,buf,strlen(buf));
		printf(buf,"xiaoming%04d",num++);
		sleep(1);
	}
	close(fd);
	return 0;
}
