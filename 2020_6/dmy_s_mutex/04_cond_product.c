#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

typedef struct _ProdInfo{
	int num;
	struct _ProdInfo *next;
}ProdInfo;
int beginnum = 1000;
ProdInfo *head = NULL;

void *thr_productor(void *arg){
	while(1){
		ProdInfo* prod = malloc(sizeof(ProdInfo));
		prod->num = beginnum++;
		printf("---%s---self=%lu---%d\n",__FUNCTION__,pthread_self(), prod->num);
		pthread_mutex_lock(&mutex);
		prod->next = head;
		head = prod;
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond);
		sleep(rand()%4);
	}
	return NULL;
}

void *thr_customer(void* arg){
	ProdInfo *prod = NULL;
	while (1){
		pthread_mutex_lock(&mutex);
		if(head == NULL){
			pthread_cond_wait(&cond, &mutex);
		}
		prod = head;
		head = head->next;
		printf("---%s---self=%lu---%d\n",__FUNCTION__,pthread_self(), prod->num);
		pthread_mutex_unlock(&mutex);
		sleep(rand()%4);
		free(prod);
	}

return NULL;
}

int main(){
	pthread_t tid[2];
	pthread_create(&tid[0],NULL,thr_productor,NULL);
	pthread_create(&tid[1],NULL,thr_customer,NULL);

	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	
	//pthread_cond_destory(&cond);
	//pthread_mutex_destory(&mutex);
	return 0;
}
