#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int spawn_grep(char* word,char* file){
	int pid;
	if((pid=fork())==0){
		
		if(execlp("grep","grep",word,file,NULL)<0){
			perror("exec");
		}
	}
	
	if(pid==-1)perror("fork");
	

	return pid;

}

int main(int argc,char* argv[]){
	int i;
	int status;
	int pid;
	int ret;
	int pidfound;
	int pids[argc-2];

	if(argc<3){
		printf("bad usage\n");
		return -1;
	}

	for(i=0;i<argc-2;i++){
		pids[i] = spawn_grep(argv[1],argv[i+2]);
	}

	int found=0;
	
	

	while(!found && (pid=wait(&status))>0){
		if(WIFEXITED(status)){
			if(WEXITSTATUS(status)==0){
				printf("process %d found\n",pid);
				pidfound=pid;
				found=1;

				for(i=0;i<argc-2;i++){
					if(pids[i]!=pidfound && pids[i]>0){
						kill(pids[i],SIGKILL);
						waitpid(pids[i],&status,0);
						if(WIFEXITED(status)){
							printf("process %d finished already\n",pids[i]);
						}else{
							printf("process %d was interrupted\n",pids[i]);
						}
					}
				}
			}
			else printf("process %d did not found\n",pid);
		}
	}

	return !found;
}
