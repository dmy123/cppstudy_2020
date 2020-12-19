#include <stdio.h>
#include <unistd.h>
int main()
{
	char buf[32] = {0};
	readlink("hellow.soft1",buf,sizeof(buf));
	//readlink("hello.hard1",buf,sizeof(buf));
	printf("buf is %s\n",buf);
	unlink("hellow.soft1");
	return 0;
}
