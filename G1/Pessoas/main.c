#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BD "basedados"
#define SIZE 64
struct estrutura{
	char nome[SIZE];	
	int idade;
};

int main(int argc, char *argv[]){
	//verifica se tem 4 argumentos
	if(argc!=4){
		printf("Nr de campos errado\n");
		return -1;
	}	
	
	//verifica o primeiro arg
	if(argv[1][0]!='-' ){
		printf("primeiro argumento tem de começar por '-'");
		return -1;
	}
	
	
	//op -i
	if(argv[1][1]=='i'){
		int d1 = open(BD, O_WRONLY | O_APPEND | O_CREAT,0644);
		if(d1<0){
			perror(BD);
			return -1;
		}
		
		//printf("-i\n");
		struct estrutura s;
		//memset(s.nome,'0',SIZE);
		strcpy(s.nome,argv[2]);
		s.idade = atoi(argv[3]);
		
		write(d1,&s,sizeof(struct estrutura));
		
		//off_t lseek(int fd, off_t offset, int whence)
		printf("Registo %ld\n",lseek(d1,-1*sizeof(struct estrutura),SEEK_CUR)/sizeof(struct estrutura));

		close(d1);
		return 0;
	}
	
	//op -u
	if(argv[1][1]=='u'){

		int d1 = open(BD,O_RDWR);
		if(d1<0){
            perror(BD);
            return -1;
        }

		struct estrutura s;
		int o;
		while((o = read(d1,&s,sizeof(struct estrutura)))>0){
			if(strcmp(s.nome,argv[2])==0){
				//printf("encontrei %s==%s\n",s.nome,argv[2]);
				s.idade=atoi(argv[3]);
				//escrever estrutura
				//off_t lseek(int fd, off_t offset, int whence)
				lseek(d1,-1*sizeof(struct estrutura),SEEK_CUR);
				write(d1,&s,sizeof(struct estrutura));
				break;
			}
		}
                
		close(d1);
		return 0;
        	

	}

	if(argv[1][1]=='l'){
        int d1 = open(BD,O_RDWR);
        struct estrutura s;
		int o;
		if(d1<0){
            perror(BD);
            return -1;
        }

        while((o = read(d1,&s,sizeof(struct estrutura)))>0){
            printf("%s,%d\n",s.nome,s.idade);
        }
		return 0;
	}
	printf("opcao nao valida");
	return -1;

}
