#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv){
	int ret;
	
	char *exec_args[]={"/bin/ls","-l",NULL};

	//exect(_) -> _ indica como é expecificado o caminho
	//primeiro campo -> 
	//campos seguintes -> argumentos do comando (primeiro argumento é sempre o nome do comando
	//ultimo campo -> NULL, para saber que acabaram os argumentos
	
	
	ret = execl("/bin/ls", "/bin/ls","-l",NULL); //
	
	//ret = execlp() // lp -> currentPath
	
	//ret = execv("/bin/ls",exec_args); //so recebe o executavel e o array de strings que contem os argumentos do novo programa 

	
	//se exec returnar -1 , se nao o resto do codigo nao se executa, o programa é substituido pelo usado 	

	printf("ola\n");
	perror("reached return");


	return 0;
}
