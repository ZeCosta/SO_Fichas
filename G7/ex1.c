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
        seg++;
	alarm(1);
}


int main(){
	signal(SIGINT,sigint_handler);	
	signal(SIGQUIT,sigquit_handler);
	signal(SIGALRM,sigalrm_handler);

	alarm(1);
	while(1){
		pause();
		printf("teste\n");
	}

	return 0;
}
