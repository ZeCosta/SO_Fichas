#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_ARG_SIZE 1024

int main (int argc, char* argv[]){
	char buf[MAX_ARG_SIZE];
	int bytes_read;
	int logfile, fd;

	if((logfile=open("log.txt",O_CREAT | O_TRUNC | O_WRONLY,  0666))==-1){
		perror("open log");
		return -1;
	}

	if(mkfifo("fifo",0666)==-1){
		perror("mkfifo");
		return -1;
	}

	while(1){//usar sinais em vez de 1
		if((fd=open("fifo",O_RDONLY))==-1){
			perror("open fifo");
		}
		else{
			printf("|DEBUG| opened file for reading\n");
		}
		
		while((bytes_read = read(fd,buf,MAX_ARG_SIZE))>0){
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
