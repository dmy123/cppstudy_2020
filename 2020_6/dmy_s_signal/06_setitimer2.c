#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
void cat_sig(int num)
{
	printf("cat %d sig\n",num);
}
int main()
{
	signal(SIGALRM,cat_sig);
	struct itimerval myit = {{3,0},{5,0}};
	setitimer(ITIMER_REAL,&myit,NULL);
	while(1){
		printf("who can kill me\n");
		sleep(1);
	}
	return 0;
}
