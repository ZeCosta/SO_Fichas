#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_ARG_SIZE 1024

int fd;
int op=1;
void sigint_handler(int sig){
	op=0;
	printf("cenas %d\n",sig);
	close(fd);
	unlink("fifo");
	printf("Exiting\n");
	kill(getpid(),SIGKILL);
	//sleep(2);

}

int main (int argc, char* argv[]){
	char buf[MAX_ARG_SIZE];
	int bytes_read;
	int logfile, fd;
	
	signal(SIGINT,sigint_handler);	

	if((logfile=open("log.txt",O_CREAT | O_TRUNC | O_WRONLY,  0666))==-1){
		perror("open log");
		return -1;
	}

	if(mkfifo("fifo",0666)==-1){
		perror("mkfifo");
		//return -1;
	}
	
	
	while(op){//usar sinais em vez de 1
		//printf("Entrou no ciclo\n");
		if((fd=open("fifo",O_RDONLY))==-1){
			perror("open fifo");
			return -1;
		}
		else{
			printf("|DEBUG| opened file for reading\n");
		}
		
		while(op && (bytes_read = read(fd,buf,MAX_ARG_SIZE))>0){
			write(logfile,buf,bytes_read);
			buf[bytes_read]='\0';
			printf("|DEBUG| wrote %s to logfile\n",buf);
		}

		if(bytes_read==0) printf("|DEBUG| EOF\n");
		else perror("read");

		close(fd);
	}

	close(logfile);
	
	unlink("fifo");

	return 0;
}
