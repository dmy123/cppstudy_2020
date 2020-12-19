#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	int fd = open("test.txt",O_RDWR|O_CREAT,0666);
	if (fd < 0){
		perror("open err");
		return -1;
	}
	struct flock lk;
	lk.l_type = F_WRLCK;
	lk.l_whence = SEEK_SET;
	lk.l_start = 0;
	lk.l_len = 0;
	
	if (fcntl(fd,F_SETLK,&lk) < 0){
		perror("get lock err\n");
		exit(1);
	}
	while (1){
		printf("i am alive\n");
		sleep(1);
	}
	return 0;
}
