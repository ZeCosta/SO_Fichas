#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int pai2filho(){
	int p[2];
	char line[]="linha1";
	char buffer[20];
	int res;
	int status;

	if(pipe(p)==-1){
		perror("pipe");
		return -1;
	}
	

	switch(fork()){
		case -1:
			perror("fork");
			return -1;
		case 0:
			//filho
			//fechar descritor de escrita no filho
			close(p[1]);
			res=read(p[0],&buffer,sizeof(buffer));
			printf("[FILHO]: read %s from pipe, res %d\n", buffer, res);
			close(p[0]);
			_exit(0);
		default:
			//pai
			//fechar descritor de leitura no pai
			close(p[0]);
			write(p[1],&line,strlen(line));
			printf("[PAI]: wrote line to pipe\n");
			close(p[1]);

			wait(&status);

	}

	return 0;
}

int filho2pai(){
	int p[2];
        char line[]="linha2";
        char buffer[20];
        int res;
        int status;



	if(pipe(p)==-1){
		perror("pipe");
		return -1;
	}

	switch(fork()){
		case -1://erro
			perror("fork");
			return -1;
		case 0://filho
			close(p[0]);
			write(p[1],&line,strlen(line));
			printf("[Filho]: Escrita concluida\n");
			
			close(p[1]);
			_exit(0);			

		default://pai
			close(p[1]);
			
			res=read(p[0],&buffer,sizeof(buffer));
			printf("[PAI]: Leu %s com res=%d\n",buffer,res);
			wait(&status);
			close(p[0]);
	return 0;
	}




}

int main(){
	//pai2filho();
	filho2pai();
	return 0;
}
