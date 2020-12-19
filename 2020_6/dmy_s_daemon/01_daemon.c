#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#define _FILE_NAME_FORMAT_ "%s/2020_6/mydaemon.%ld"

void touchfile(int num){
	char *homedir = getenv("HOME");
	printf("%s\n",homedir);
	char strfilename[256] = {0};
	sprintf(strfilename,_FILE_NAME_FORMAT_,homedir,time(NULL));
	printf("open file : %s\n",strfilename);
	int fd = open(strfilename,O_RDWR|O_CREAT,0666);
	if (fd < 0){
		perror("open err");
		exit(1);
	}
	close(fd);
}

int main(){
	pid_t pid = fork();
	if (pid > 0){
		exit(1);	
	}
	setsid();
	umask(0);
	chdir(getenv("HOME"));
	struct itimerval myit = {{60,0},{1,0}};
	setitimer(ITIMER_REAL,&myit,NULL);
	struct sigaction act;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	act.sa_handler = touchfile;
	sigaction(SIGALRM,&act, NULL);
	while (1){
		sleep(1);
	}
	return 0;
}
