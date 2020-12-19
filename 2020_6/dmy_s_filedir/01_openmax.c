#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int num = 3;
	char filename[128]={0};
	while (1){
		sprintf(filename,"temp_%04d",num++);
		if (open(filename, O_RDONLY|O_CREAT,0666)< 0)
		{
			perror("OPEN ERR");
			break;
		}
	}
	printf("num == %d",num);
	return 0;
}
