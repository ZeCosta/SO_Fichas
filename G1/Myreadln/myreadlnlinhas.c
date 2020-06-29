#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

#include <stdio.h>

#define MAX 1024

char buffer[MAX];
int read_buffer_ini = 0;
int read_buffer_pos = 0;
int read_buffer_end = 0;

void readl(int fd, char *c){
	read_buffer_end = read(fd,buffer,MAX);
}

ssize_t readln(int fd, char *line, ssize_t size){
	if(read_buffer_pos==read_buffer_end){
		read_buffer_pos=0;
		readl(fd,line);
	}

	read_buffer_ini = read_buffer_pos;
        while(read_buffer_pos<read_buffer_end && line[read_buffer_pos]!='\n'){
	       	read_buffer_pos++;
	}

	return read_buffer_end;
}


int main(int argc,char* argv[]){
	//validar argumentos
	if(argc!=2){
		perror("Erro: Nr de argumentos diferente de 2");
		return(-1);
	}
	
	int o;
	int d1 = open(argv[1],O_RDONLY);
	
	while(readln(d1,buffer,MAX)){
		write(1,buffer+read_buffer_ini,(1 + read_buffer_pos-read_buffer_ini));
	}

	close(d1);
}
