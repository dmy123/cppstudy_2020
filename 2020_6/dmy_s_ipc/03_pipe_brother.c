#include <stdio.h>
#include <unistd.h>

int main(){
	int fd[2];
	pipe(fd);
	int i;
	for (i = 0;i < 2;++i){
		pid_t pid = fork();
		if (pid == 0){
			break;
		}
	}
	if (i == 2){
		close(fd[0]);
		close(fd[1]);
	} 
	if (i == 0){
		close(fd[0]);
		dup2(fd[1],1);
		execlp("ps","ps","aux",NULL);
	} 
	if (i == 1){
		close(fd[1]);
		dup2(fd[0],0);
		execlp("grep","grep","bash",NULL);
	} 
	/*
	   pid_t pid = fork();
	   if (pid == 0){
	   dup2(fd[1],1);
	   execlp("ps","ps","aux",NULL);
	   }
	   else if (pid > 0){
	   dup2(fd[0],0);
	   execlp("grep","grep","bash",NULL);
	   }*/
	return 0;
}
