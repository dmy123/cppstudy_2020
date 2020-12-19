#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc,char* argv[]){
	int fd = open("mem.txt",O_RDWR);
	char *mem = mmap(NULL,8,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if (mem == MAP_FAILED){
		perror("mmap err");
		return -1;
	}
	pid_t pid = fork();
	if(pid == 0){
		*mem = 100;
		printf("child,*mem = %d\n",*mem);
		sleep(3);
		printf("child,*mem = %d\n",*mem);
	}
	else if (pid > 0){
		sleep(1);
		printf("parent,*mem = %d\n",*mem);
		*mem = 45;
		printf("parent,*mem = %d\n",*mem);
		wait(NULL);
	}
	munmap(mem,8);
	close(fd);
	return 0;
}
