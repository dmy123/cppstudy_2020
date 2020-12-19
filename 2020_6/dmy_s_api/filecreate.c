#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char* argv[]){
	if (argc != 2)
	{
		printf("./a.out filename\n");
		return -1;
	}
	int fd = open(argv[1], O_WRONLY|O_CREAT,0666);
	int ret = lseek(fd,1024,SEEK_END);
	write(fd, "a",1);
	printf("file size is %d\n",ret);
	close(fd);
	return 0;
}
