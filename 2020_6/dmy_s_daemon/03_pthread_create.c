#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thr(void* arg){
	printf("i am a thread!pid = %d,tid = %lu\n",getpid(),pthread_self());
	return NULL;
}
int main(){
	pthread_t tid;
	pthread_create(&tid,NULL,thr,NULL);
	printf("i am a main thread,pid = %d,tid = %lu\n",getpid(),pthread_self());
	sleep(1);
	return 0;
}

