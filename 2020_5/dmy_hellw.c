#include <stdio.h>
//#include "head.h"

int main(void)
{
	int c;
	int a = 10, b = 10;
//#ifdef DMY_DEBUG
//	printf("hello world\n");
//#endif
	printf("%d + %d is %d\n", a, b, add(a, b));
	return 0;
}
int add(int a, int b)
{
	return a + b;
}
