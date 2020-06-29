#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h>/* chamadas wait*() e macros relacionadas */

#include <stdio.h>

//sequencial
int main(){
	int pid;
	int status;
	int i;
	for(i=0;i<10;i++){
		pid=fork();
		if(pid==0){
                	printf("PID= %d\n",getpid());
			printf("PPID= %d\n",getppid());
        	        _exit(i);

        	}else{
                	pid_t terminated_pid = wait(&status);
                	printf("Pai: recebi o valor %d\n",WEXITSTATUS(status));
        	}
	}

	return 0;
}
