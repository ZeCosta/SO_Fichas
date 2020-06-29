#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv){
	int i;
	pid_t fork_ret;
	int exec_ret;
	for(i=1;i<argc;i++){
		fork_ret=fork();
		if(fork_ret==0){
			exec_ret = execlp(argv[i],argv[i],NULL);
			
			perror("reached return");
			_exit(exec_ret);
		}
	}

	pid_t wait_ret;
	int status;
	for(i=1;i<argc;i++){
		wait_ret=wait(&status);
		if(WIFEXITED(status))printf("[pai] filho %d terminou com sucesso. Retornou %d\n",wait_ret,WEXITSTATUS(status));
		else printf("[pai] filho %d nao terminou\n",wait_ret);
	}

	return 0;
}
