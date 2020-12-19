#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int n = 5;
	int i = 0;
	pid_t pid = 0;
	for (i = 0;i < 5;++i)
	{
		pid = fork();
		if (pid == 0)
		{
			printf("i am child,pid = %d,ppid = %d\n",getpid(), getppid());
			break;
		}
		else if (pid > 0)
		{
			//printf("i am father,pid = %d,ppid = %d\n",getpid(), getppid());
		}
	}
	if (i < 5)
	{

		printf("i am child,i will exit,pid = %d,ppid = %d\n",getpid(), getppid());
		return 0;	
	}
	else
	{
		printf("i am father,pid = %d,ppid = %d\n",getpid(), getppid());
	}
	while (1)
	{
		sleep(1);
	}
	return 0;
}
