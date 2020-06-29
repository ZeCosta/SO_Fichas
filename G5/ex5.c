#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(){
	int p[3][2];
    int res=0;
    int status;
	int pid;
	int N=3;
	char cmd[10][10]={"ls","uniq","wc"};
    int i;
	
	for(i=0;i<N;i++){
		if(i==0){
			if(pipe(p[i])==-1){
                perror("Pipe");
                return -1;
            }
			
    		switch((pid=fork())){
               	case -1:
                    perror("Fork");
                 	return -1;
                case 0:
             		close(p[i][0]);
                   	dup2(p[i][1],1);
                  	close(p[i][1]);

                     res=execlp(cmd[i],cmd[i],NULL);
                   	_exit(0);
                            
    			default:
                    printf("Forked\n");
    				close(p[i][1]);
            }
		}
		
		else if(i==N-1){
			switch((pid=fork())){
                case -1:
                    perror("Fork");
                    return -1;
                case 0:
                    dup2(p[i-1][0],0);
                    close(p[i-1][0]);

                    res=execlp(cmd[i],cmd[i],NULL);
                   _exit(0);

                default:
                    printf("Forked\n");
                }
	
		}
		
		
		else{
			if(pipe(p[i])==-1){
                perror("Pipe");
                return -1;
            }

            switch((pid=fork())){
                case -1:
                    perror("Fork");
                    return -1;
                case 0:
                    dup2(p[i-1][0],0);
                    close(p[i-1][0]);

                    close(p[i][0]);
                    dup2(p[i][1],1);
                    close(p[i][1]);

                    res=execlp(cmd[i],cmd[i],NULL);
                    _exit(0);

                default:
                    printf("Forked\n");
                    close(p[i][1]);
            }
		}

	}
	
	for(i=0;i<N;i++){
		wait(&status);
	}

	return 0;
}


