#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid = fork();
	if (pid == 0){
		printf("i am child,pid=%d,ppid=%d",getpid(),getppid());
		while (1){
			printf("i am child,pid=%d,ppid=%d",getpid(),getppid());
			sleep(1);
		}
	}
	else if(pid > 0){
		printf("i am parent,pid=%d,ppid=%d",getpid(),getppid());
		sleep(5);
		printf("i am parent,i am died");
	}
	return 0;
}
		
