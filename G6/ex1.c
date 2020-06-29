#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (){
	if(mkfifo("fifo",0666)==-1){
		perror("mkdir fifo");
	}

	return 0;
}
