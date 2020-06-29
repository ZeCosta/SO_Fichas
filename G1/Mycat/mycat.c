#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

#include <stdio.h>

#define MAX 1
int main(){
	char buffer[MAX]; //char representa 1byte e nao por ser um ficheiro de texto
	int n;
	
	while((n = read(0,buffer,MAX)) > 0){ //n = quantos caracteres sao lidos, >0 -> se copiou algo
		write(1,buffer,n);
	}
	return 0;
}
