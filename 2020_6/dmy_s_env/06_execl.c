#include <unistd.h>
#include <stdio.h>

int main()
{
	//execlp("ls","ls","-l",NULL);
	//execl("dfyubin/ls","ls","-l","--color=auto",NULL);
	execl("./04_nfork","./04_nfork",NULL);
	perror("exec err");
	printf("hello\n");
	return 0;
}
