#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char* argv[])
{
	if (argc != 2){
		printf("./a.out filename\n");
		return -1;
	}
	int fd = open(argv[1],O_RDWR);
	if (fd < 0)
	{
		perror("open err");
		_exit(1);
	}
	pid_t pid = fork();
	if (pid ==0)
	{
		write(fd,"hello\n", 6);
	}
	else if (pid > 0)
	{
		sleep(1);
		write(fd,"world\n",6);
		wait(NULL);
	}
	return 0;
}
