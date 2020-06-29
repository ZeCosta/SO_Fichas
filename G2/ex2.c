#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h>/* chamadas wait*() e macros relacionadas */

#include <stdio.h>

int main(){
	int n;
	if((n=fork())==0){

                printf("Sou filho - pid: %d\n",getpid());
                printf("Sou filho - ppid: %d\n",getppid());

		_exit(0);
	}else{  
		printf("Sou pai - pid: %d\n",getpid());
                printf("Sou pai - ppid: %d\n",getppid());
                printf("Sou pai - pid do filho: %d\n",n);

	}

	return 0;
}
