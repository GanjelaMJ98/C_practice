#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	pid_t pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (!pid){
		const char *args[] = {"fork", NULL};
		int ret;

		ret = execv("./fork", args);
		if(ret == -1){
			perror("execv");
			exit(EXIT_FAILURE);	
		}
	}
	
		
return 0;
}