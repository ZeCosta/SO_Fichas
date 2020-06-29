#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h>/* chamadas wait*() e macros relacionadas */

#include <stdio.h>
 
//descendente
int main(){
        int nproc=10;
        pid_t pid;
        int status;

        for(int i=0;i<nproc;i++){
                if((pid=fork())==0){
                        printf("[proc #%d] pid: %d\n",i,getpid());
                        _exit(i);
                }
        }

        for(int i=0;i<nproc;i++){
                pid_t terminated_pid = wait(&status);

                if(WIFEXITED(status)){
                        printf("[pai] process %d exited, exit code: %d\n",terminated_pid,WEXITSTATUS(status));
                }else{
                        printf("[pai] process %d exited.\n",terminated_pid);
                }
        }
        return 0;
}

