#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv){
	if(argc>1) strcpy(argv[1], "-l");
	
	//comparar system a execv
	printf("System\n");
	int a = system("ls");
	printf("ret: %d\n",a);
	
	//char *args[]={"ls","\0"};
	printf("---------\nexecv:\n");
	int e=execvp("ls",argv);
	printf("ret: %d\n",e);

	
	printf("---------------------------\n-------------------------\n Exercicio:\n");

	//exercicio
	int ret = execv("ex3", argv);

	return ret;
}
