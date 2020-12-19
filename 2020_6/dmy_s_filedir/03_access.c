#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

int main(int argc,char* argv[])
{
	if (argc != 2)
	{
		printf("./a.out filename\n");
		return -1;
	}
	if (access(argv[1],R_OK) == 0) printf("%s read ok\n",argv[1]);
	if (access(argv[1],W_OK) == 0) printf("%s write ok\n",argv[1]);
	if (access(argv[1],X_OK) == 0) printf("%s exe ok\n", argv[1]);
	if (access(argv[1],F_OK) == 0) printf("%s file exists!\n",argv[1]);
	return 0;
}
