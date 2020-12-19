#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/listener.h>
#include <arpa/inet.h>

void read_cb(struct bufferevent *bev, void *ctx){
	char buf[1024] = {0};
	int len = bufferevent_read(bev,buf,sizeof(buf));
	printf("client recv buf: %s\n",buf);
	bufferevent_write(bev,buf,len + 1);
	printf("client buf send\n");
}


void write_cb(struct bufferevent *bev, void *ctx){
	printf("client message already send\n");
}

void event_cb(struct bufferevent *bev,short events, void *ctx){
	if (events & BEV_EVENT_EOF){
		printf("client connection closed\n");
	}
	if (events & BEV_EVENT_ERROR){
		printf("client some other error\n");
	}
	if (events & BEV_EVENT_CONNECTED){
		printf("client already connected\n");
		return ;
	}
	bufferevent_free(bev);
}


void read_terminal(evutil_socket_t fd,short what, void* arg){
	char buf[1024] = {0};
	int len = read(fd,buf,sizeof(buf));
	struct bufferevent* bev = (struct bufferevent*)arg;
	bufferevent_write(bev,buf,strlen(buf) + 1);
}

int main(int argc,const char* argv[]){
	struct event_base* base = event_base_new();
	
	int fd = socket(AF_INET,SOCK_STREAM,0);
	struct bufferevent* bev = bufferevent_socket_new(base,fd,BEV_OPT_CLOSE_ON_FREE);

	struct sockaddr_in serv;
	memset(&serv, 0,sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8765);
	inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr.s_addr);
	int ret = bufferevent_socket_connect(bev,(struct sockaddr*)&serv,sizeof(serv));
	bufferevent_setcb(bev,read_cb,write_cb,event_cb,NULL);

	struct event* ev = event_new(base,0,EV_READ|EV_PERSIST
	,read_terminal,bev);
	event_add(ev,NULL);

	event_base_dispatch(base);
	event_base_free(base);
	return 0;
}
