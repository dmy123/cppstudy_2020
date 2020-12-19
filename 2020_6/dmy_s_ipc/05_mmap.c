#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

int main(int argc,char* argv[]){
	int fd = open("mem.txt",O_RDWR);
	char *mem = mmap(NULL,8,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if (mem == MAP_FAILED){
		perror("mmap err");
		return -1;
	}

	close(fd);	
	strcpy(mem,"hello");
	int ret = munmap(mem,8);
	if (ret < 0)
	{
		perror("munmap err");
	}
	//close(fd);	
	return 0;
}
