#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	symlink("hello","hellow.soft1");
	//link("hello","hellow.hard1");
	return 0;
}
