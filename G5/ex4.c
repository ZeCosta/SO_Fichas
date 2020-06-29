#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(){
	int p[2];
        int res=0;
        int status;
	int pid;

        if(pipe(p)==-1){
                perror("pipe");
                return -1;
        }


        switch((pid=fork())){
                case -1:
                        perror("fork");
                        return -1;
                case 0:
                        //filho
                        //fechar descritor de escrita no filho
                        close(p[1]);

			dup2(p[0],0);
			close(p[0]);
			res=execlp("wc","/bin/wc","-l",NULL);
                        _exit(0);

                default:
                        //pai
                        //fechar descritor de leitura no pai
                        close(p[0]);
			
	}

	switch((pid=fork())){
		case-1 :
		     perror("fork2");
		     return -1;
		case 0:
		     	//filho 2
			dup2(p[1],1);
		     	close(p[1]);

			res=execlp("ls","/bin/ls",NULL);
			_exit(0);
		default:
			close(p[1]);
    			printf("PAI\n");

	}

	wait(&status);
	wait(&status);

	return 0;
}
