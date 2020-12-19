#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("Begin ....\n");
	pid_t pid = fork();
	if (pid < 0)
	{
		perror("fork err");
	}
	if (pid ==0)
	{
		printf("i am child,pid = %d,ppid = %d\n",getpid(),getppid());
		while (1)
		{
			printf("i am child\n");
			sleep(1);
		}
	}
	else if (pid > 0)
	{
		printf("childpid=%d,self=%d,ppid=%d\n",pid,getpid(),getppid());
		sleep(1);
	}
	printf("End ....\n");
	return 0;
}
