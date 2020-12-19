#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

void catch_sig(int num)
{
	pid_t wpid = waitpid(-1,NULL,WNOHANG);
	if (wpid > 0){
		printf("wait child %d ok\n",wpid);
	}
}
int main(){
	sigset_t myset, oldset;
	sigemptyset(&myset);
	sigaddset(&myset, SIGCHLD);
	sigprocmask(SIG_BLOCK,&myset,&oldset);
	int i = 0;
	pid_t pid;
	for (i = 0;i < 10;++i){
		pid = fork();
		if (pid == 0) {
			break;
		}
	}

	if (i == 10){
		struct sigaction act;
		act.sa_handler = catch_sig;
		act.sa_flags = 0;
		sigemptyset(&act.sa_mask);
		sleep(4);
		sigaction(SIGCHLD,&act, NULL);
		sigprocmask(SIG_SETMASK,&oldset,NULL);
		while(1){
			sleep(1);
		}
	}else{
		printf("i am %d child,pid = %d\n",i,getpid());
		sleep(i);
	}
	return 0;
}
