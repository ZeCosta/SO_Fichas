#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int seg=0;
int ctrc=0;

void sigint_handler(int sig){
	ctrc++;
	printf("seg=%d\n",seg);
}
void sigquit_handler(int sig){
        printf("ctr+c=%d\n",ctrc);
	exit(0);
}
void sigalrm_handler(int sig){
    printf("ola\n");
}

int pid;
int main(){
	signal(SIGALRM,sigalrm_handler);
	int status;
	alarm(2);

	switch((pid=fork())){
		case -1:
			perror("fork");
			return -1;
		case 0:
			printf("filho\n");
			_exit(0);
		default:
	}

	printf("wait -> %d\n",wait(&status));
	

	return 0;
}
