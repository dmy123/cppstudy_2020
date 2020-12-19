#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <event2/event.h>

void read_cb(evutil_socket_t fd,short what,void* arg){
	char buf[1024] = {0};
	int len = read(fd,buf,sizeof(buf));
	printf("data len = %d,buf = %s\n",len,buf);
	printf("read event: %s\n",what & EV_READ?"YES":"NO");
	sleep(10);
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
	unlink("myfifo");
	mkfifo("myfifo",0644);
	int fd = open("myfifo",O_RDONLY|O_NONBLOCK);
	if (fd == -1){
		perror("open error");
		exit(1);	
	}
	struct event_base* base;
	base = event_base_new();
	
	struct event* ev = event_new(base,fd,EV_READ|EV_PERSIST,read_cb,NULL);
	int res = event_add(ev,NULL);
	event_base_dispatch(base);
	event_free(ev);
	event_base_free(base);
	close(fd);
	return 0;
}
