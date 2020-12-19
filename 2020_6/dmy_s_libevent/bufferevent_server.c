#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/listener.h>

void read_cb(struct bufferevent *bev, void *ctx){
	char buf[1024] = {0};
	bufferevent_read(bev,buf,sizeof(buf));
	printf("recv buf: %s\n",buf);
	char * pt = "recv success!";
	bufferevent_write(bev,pt,strlen(pt) + 1);
	printf("server: message send\n");
}


void write_cb(struct bufferevent *bev, void *ctx){
	printf("message already send\n");
}

void event_cb(struct bufferevent *bev,short events, void *ctx){
	if (events & BEV_EVENT_EOF){
		printf("connection closed\n");
	}
	if (events & BEV_EVENT_ERROR){
		printf("some other error\n");
	}
	bufferevent_free(bev);
}

void listen_cb(struct evconnlistener * listener,
	evutil_socket_t fd,
	struct sockaddr* addr,
	int len,void *ptr)
{
	struct event_base* base = (struct event_base*)ptr;
	struct bufferevent* bev = NULL;
	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev, read_cb,write_cb,event_cb,NULL);
	bufferevent_enable(bev,EV_READ);
	return ;
}

int main(int argc,const char* argv[]){
	pid_t pid = fork();
	if (pid > 0){
		exit(1);	
	}
	setsid();
	umask(0);
	chdir(getenv("HOME"));
	
	struct event_base* base = NULL;
	base = event_base_new();
	
	struct sockaddr_in serv;
	memset(&serv,0,sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8765);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);

	struct evconnlistener* listen = NULL;
	listen = evconnlistener_new_bind(base,
listen_cb,base,LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE,
-1,(struct sockaddr*)&serv,sizeof(serv));
	event_base_dispatch(base);
	evconnlistener_free(listen);
	event_base_free(base);
	return 0;
}
