#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char **argv){
	char *exec_args[]={"/bin/ls","-l",NULL};

	
	int fork_ret = fork();

	if(fork_ret==0){
		printf("Sou filho %d\n",getpid());

		int exec_ret=execv("/bin/ls",exec_args);

		perror("reached return");
		
		printf("cenas\n");
		_exit(exec_ret);
	}else{
		printf("Sou pai%d\n",getpid());
		
		int status;
		int wait_ret=wait(&status);
		
		if(WIFEXITED(status))printf("O filho retornou %d\n", WEXITSTATUS(status));
		else printf("o filho nao terminou");
	}


	return 0;
}
