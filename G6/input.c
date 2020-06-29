#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, char* argv[]){
	if(argc < 2){
		printf("falta args\n");
		return -1;
	}
	int fd=open("fifo",O_WRONLY);
	if(fd==-1){
		perror("Open");
		return -1;
	}
	else{
		printf("|DEBUG| opened fifo for writing\n");
	}

	if(write(fd,argv[1],strlen(argv[1]))==-1){
		perror("write");
	}

	close(fd);

	return 0;
}
