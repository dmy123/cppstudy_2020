#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
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
	}
	if (i == 5)
	{
		while (1){
			pid_t wpid = waitpid(-1, NULL,WNOHANG);
			if (wpid == -1) break;
			else if (wpid > 0){
				printf("waitpid wpid= %d\n",wpid);
			}
		}
		while(1){
			sleep(1);
		}	

	}
	if (i < 5)
	{
		printf("i am child\n");
	}

	return 0;
}
