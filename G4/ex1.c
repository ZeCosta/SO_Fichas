#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, char* argv[]){
	int res=0;
	int i=0;
	char buffer;
	char line[1024];



	int ifd=open("/etc/passwd",O_RDONLY);
	int ofd=open("a1_saida.txt",O_CREAT|O_TRUNC|O_WRONLY,0666);
	int efd=open("a2_erros.txt",O_CREAT|O_TRUNC|O_WRONLY,0666);

	res=dup2(ifd,0);
	res=dup2(ofd,1);
	res=dup2(efd,2);



	close(ifd);
	close(ofd);
	close(efd);


	int nr_lines=12;
	while(nr_lines>0){
		i=0;
		while(read(0,&buffer,1)!=0){
			line[i]=buffer;
			i++;
			if (buffer=='\n'){
				break;
			}
		}

		write(1,line,i);
		write(2,line,i);

		nr_lines-=1;
		//printf("%d\n",nr_lines);
	}
}