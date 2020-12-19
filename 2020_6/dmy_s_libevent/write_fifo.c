#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <event2/event.h>

void write_cb(evutil_socket_t fd,short what,void* arg){
	char buf[1024] = {0};
	static int num = 0;
	sprintf(buf,"hello, word = %d\n",num++);
	int len = write(fd,buf,strlen(buf) + 1);
	sleep(10);
//	printf("data len = %d,buf = %s\n",len,buf);
//	printf("read event: %d\n",what & EV_READ?"YES":"NO");
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
//	unlink("myfifo");
//	mkfifo("myfifo",0644);
	int fd = open("myfifo",O_WRONLY|O_NONBLOCK);
	if (fd == -1){
		perror("open error");
		exit(1);	
	}
	struct event_base* base;
	base = event_base_new();
	
	struct event* ev = event_new(base,fd,EV_WRITE|EV_PERSIST,write_cb,NULL);
	int res = event_add(ev,NULL);
	event_base_dispatch(base);
	event_free(ev);
	event_base_free(base);
	close(fd);
	return 0;
}
