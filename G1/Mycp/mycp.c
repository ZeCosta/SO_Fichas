#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

#include <stdio.h>

#define MAX 4000
int main(int argc,char* argv[]){
	//validar argumentos
	if(argc!=3){
		printf("Erro: Nr de argumentos diferente de 3");
		return (-1);
	}
	
	//corpo do cp
	



	int d1= open(argv[1],O_RDONLY);
	if(d1<0){
		perror(argv[1]);
		return (-2);
	}


	int d2= open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, 0644);
	

	char buffer[MAX]; //char representa 1byte e nao por ser um ficheiro de texto
	int n;
	
	while((n = read(d1,buffer,MAX)) > 0){ //n = quantos caracteres sao lidos
		write(d2,buffer,n);
	}

	close(d1);
	close(d2);
	return 0;
}
