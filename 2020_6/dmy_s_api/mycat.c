#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("./a.out filename\n");
		return -1;
	}
	int fd = open(argv[1],O_RDONLY);
	char buf[256];
	int ret = read(fd, buf, sizeof(buf));
	write(STDOUT_FILENO,buf,ret);
	close(fd);
	return 0;
}
