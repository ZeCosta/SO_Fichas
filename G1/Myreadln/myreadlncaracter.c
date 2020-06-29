#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

#include <stdio.h>

#define MAX 1024

int readc(int fd, char *c){
	return read(fd,c,1);
}

ssize_t readln(int fd, char *line, ssize_t size){
	int i=0;
	int res=0;
	while(i<size && (res=readc(fd,&line[i]))>0){
		i++;
		if(((char*)line)[i-1]=='\n')return i;	
	}
	return i;
}


int main(int argc,char* argv[]){
	//validar argumentos
	if(argc!=2){
		perror("Erro: Nr de argumentos diferente de 2");
		return(-1);
	}
	
	int o;
	int d1 = open(argv[1],O_RDONLY);
	char buffer[MAX];
	while((o=readln(d1,buffer,MAX))){
		//printf("novalinha\n");
		//printf("%s",buffer);  //não dá!
		//for(int i=0; i<o;i++)printf("%c",buffer[i]); //funciona mas deve se usar o write
		write(1,buffer,o);
	}

	close(d1);

	
}
