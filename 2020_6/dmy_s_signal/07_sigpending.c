#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(){
	sigset_t pend;
	sigpending(&pend);
	int i = 1;
	for (i = 1;i < 32;++i){
		if (sigismember(&pend,i) == 1){
			printf("1");
		}
		else{
			printf("0");
		}
	}
	printf("\n");
	return 0;
}
