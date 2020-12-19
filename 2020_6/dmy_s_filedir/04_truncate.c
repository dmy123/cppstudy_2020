#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
truncate("hello",1024);
return 0;
}
