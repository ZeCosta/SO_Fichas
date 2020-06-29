#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h>/* chamadas wait*() e macros relacionadas */

#include <stdio.h>

//descendente
/*
void desc(int n){
	int pid;
	int status;
	if(n>0){
		if((pid=fork())==0){
	                printf("%d -> pid: %d\n",n,getpid());
	                printf("%d -> ppid: %d\n",n,getppid());
			desc(n-1);
        	        _exit(n);
        	}else{
			pid_t terminated_pid = wait(&status);
		}
	}
}
*/

int main(){
	pid_t pid;
	int nproc = 10;
	int status;

	for(int i=0;i<nproc;i++){
		if((pid=fork())==0){
			printf("[proc #%d] pid: %d\n",i,getpid());
		}else{
			pid_t terminated_pid = wait(&status);

			if(WIFEXITED(status)){
				printf("[pai] process %d exited, exit code: %d\n",terminated_pid, WEXITSTATUS(status));
			}else{
				printf("[pai] process %d exited.\n",terminated_pid);
			}

			_exit(0);
		}
	}

	printf("saí do cíclo pid %d\n",getpid());

	_exit(0);

	return 0;
}
