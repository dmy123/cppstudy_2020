#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

void catch_sig(int num)
{
	printf("catch %d sig\n", num);
}
int main(){
	struct sigaction act;
	act.sa_handler = catch_sig;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGALRM,&act, NULL);
	struct itimerval myit = {{3,0},{5,0}};
	setitimer(ITIMER_REAL,&myit, NULL);
	while (1){
		printf("who can kill me\n");
		sleep(1);
	}
	return 0;
}
