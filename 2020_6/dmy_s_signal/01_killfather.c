#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
int main()
{
	int i;
	for (i = 0;i < 5;++i)
	{
		pid_t pid = fork();
		if (pid == 0){
			break;
		}
	}
	if (i == 2){
		printf("i will kill father\n");
		sleep(1);
		kill(getppid(), SIGKILL);
		while (1){
			sleep(1);
		}
	}
	else if (i == 5){
		while (1){
			printf("i am father,haha\n");
			sleep(1);
		}
	}
	return 0;
}
