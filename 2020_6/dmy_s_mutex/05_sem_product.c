#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdlib.h>

sem_t blank,xfull;
#define  blankcount 5

int queue[blankcount];
int beginnum = 100;

void *thr_productor(void *arg){
	int i =0;
	while(1){
		sem_wait(&blank);
		printf("---%s---self=%lu---%d\n",__FUNCTION__,pthread_self(), beginnum);
		queue[(i++) % blankcount] = beginnum++;
		sem_post(&xfull);	
		sleep(rand()%3);
	}
	return NULL;
}

void *thr_customer(void* arg){
	int i = 0;
	while (1){
		sem_wait(&xfull);
		int eat = queue[(i++) % blankcount];
		printf("---%s---self=%lu---%d\n",__FUNCTION__,pthread_self(), eat);
		sem_post(&blank);
		sleep(rand()%4);
	}

	return NULL;
}

int main(){
	sem_init(&blank,0,blankcount);
	sem_init(&xfull,0,0);
	pthread_t tid[2];
	pthread_create(&tid[0],NULL,thr_productor,NULL);
	pthread_create(&tid[1],NULL,thr_customer,NULL);

	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);

	//pthread_cond_destory(&cond);
	//pthread_mutex_destory(&mutex);
	return 0;
}
