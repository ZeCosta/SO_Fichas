#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_LINE_SIZE 1024

ssize_t readln(int fildes,void* buf,size_t nbyte){
	ssize_t res=0;
	int i=0;

	while(i<nbyte && (res=read(fildes,&buf[i],1))>0){
		if(((char*)buf)[i]=='\n'){return i+1;}
		i+=1;
	}

	return i;
}

int main(){
	int p[2];
        int res=0;
        int status;
	int pid;
	char buffer[MAX_LINE_SIZE];

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
			res=execlp("wc","/bin/wc",NULL);
                        _exit(0);

                default:
                        //pai
                        //fechar descritor de leitura no pai
                        close(p[0]);
			printf("PAI\n");

			while((res=readln(0,buffer,MAX_LINE_SIZE))>0){
				write(p[1],buffer,res);			
			}
                        
                        close(p[1]);
                        wait(&status);
			if(WIFEXITED(status))printf("[PAI] Filho terminou com %d\n",WEXITSTATUS(status));


        }
        return 0;

}
