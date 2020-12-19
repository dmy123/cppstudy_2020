#include <stdio.h>
#include <unistd.h>

int main(){
	int fd[2];
	pipe(fd);
	pid_t pid = fork();
	if (pid == 0){
		dup2(fd[1],1);
		execlp("ps","ps","aux",NULL);
	}
	else if (pid > 0){
		dup2(fd[0],0);
		execlp("grep","grep","bash",NULL);
	}
	return 0;
}
