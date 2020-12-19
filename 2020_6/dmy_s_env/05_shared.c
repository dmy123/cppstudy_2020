#include <stdio.h>
#include <unistd.h>

int var = 100;

int main()
{
	pid_t pid = fork();
	if (pid == 0){
		printf("var = %d,child,pid = %d.ppid = %d\n",var, getpid(),getppid());
		var = 1001;
		printf("var = %d,child,pid = %d.ppid = %d\n",var, getpid(),getppid());
	}
	else{
		sleep(1);	
		printf("var = %d,parent,pid = %d.ppid = %d\n",var, getpid(),getppid());
	}
	return 0;
}
