#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

int main(int argc,char* argv[])
{
	int fd = open("world",O_WRONLY|O_CREAT,0666);
	unlink("world");
	int ret = write(fd,"hello",5);
	if (ret > 0){
		printf("write ok!%d\n",ret);
	}
	if (ret < 0)
	{
		perror("WRITE ERR");
	}
	close(fd);
	return 0;
}
