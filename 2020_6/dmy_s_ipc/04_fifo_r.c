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
	char buf[256];
	int ret;
	while (1){
		ret = read(fd,buf,sizeof(buf));
		if (ret > 0){
			printf("read:%s\n",buf);
		}
	}
	close(fd);
	return 0;
}
