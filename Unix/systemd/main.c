#include <stdio.h>
#include <syslog.h>

#define DEBUG


int main(){
	openlog("test",LOG_PID,LOG_USER);
	while(1){
		int i=0;
		printf("%s\n", "Hello,World!");
		#ifdef DEBUG
			syslog(LOG_DEBUG,"try to sending 10 messages");
		#endif
		for (i=0;i<10;i++){
			syslog(LOG_INFO,"info message [i = %d] ",i);
		};
		sleep(3);
	}
	closelog();
}