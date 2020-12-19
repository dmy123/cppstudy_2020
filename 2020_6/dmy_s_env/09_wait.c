#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid = fork();
	if (pid == 0){
		printf("i am child,pid=%d,ppid=%d\n",getpid(),getppid());
		sleep(1);
		printf("i am child,i will die\n");
		return 101;
	}
	else if(pid > 0){
		printf("i am parent,wait for child die\n");
		int status;
		pid_t wpid = wait(&status);
		//pid_t wpid = wait(NULL);
		//printf("i am parent,pid=%d,ppid=%d\n",getpid(),getppid());
		printf("wait ok,wpid=%d,pid=%d\n",wpid,pid);
		if (WIFEXITED(status))
		{
			printf("child exit with %d\n",WEXITSTATUS(status));
		}
		if (WIFSIGNALED(status))
		{
			printf("child kill by %d\n",WTERMSIG(status));
		}
		while (1){
			sleep(1);
		}
	}
	return 0;
}

