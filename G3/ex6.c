#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int mysystem(char *comando){
	char *args[20];
	int i=0;
	char *parte = strtok(comando," ");
	while(parte!=NULL){
		args[i] = parte;
		parte=strtok(NULL," ");
		i++;
	}
	args[i]='\0';


	int s_fork=fork();
	if(s_fork==0){
		int exec_ret=execvp(args[0],args);
		
		perror("reached return");
		_exit(exec_ret);
	}else{
		if (s_fork==-1)return -1;
		int status;
		pid_t wait_ret=wait(&status); //retorna o  pid do processeo que terminou		
		if(WIFEXITED(status))return WEXITSTATUS(status);
		else return -1;
	}

}

int main(int argc, char **argv){
	int ret;
	char comando1[]="clear";
	char comando2[]="ls -l";
	char comando3[]="ps";

	//printf("%s\n",argv[0]);
	//printf("%s\n",argv[1]);	
	
	ret = mysystem(comando1);
	printf("ret: %d\n",ret);

	ret = mysystem(comando2);
	printf("ret: %d\n",ret);

	ret = mysystem(comando3);
	printf("ret: %d\n",ret);
	return 0;
}
