#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int main(){
	pid_t pid;

	pid = fork();
	if (pid > 0){
		printf("I'm papa, cpid = %d\n", pid);
		//kill(pid,9);
	}
	else if (!pid)
		printf("I'm son,  pid = %d\n", pid);
	else if (pid == -1)
		perror("fork");
return 0;
}