#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("./a.out filename\n");
		return -1;
	}
	int fd = open(argv[1],O_RDWR|O_CREAT,0666);
	write(fd, "helloworld",11);
	lseek(fd,0,SEEK_SET);
	char buf[256]={0};
	int ret = read(fd,buf, sizeof(buf));
	printf("ret=%d",ret);
	if (ret)
	{
		write(STDOUT_FILENO,buf, ret);
	}
	close(fd);
	return 0;
}
