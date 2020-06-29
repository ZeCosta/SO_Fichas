#include <unistd.h>

int readln(int fd,char* line, size_t size){
	int i=0;
	int n=0;
	while(i!=size){
	       	if((n=read(fd,line+i,1)==1))i++;
		else return n;
		if(line[i-1]=='\n')break;
	}
	return i;
}

#ifdef __TEST__
#include <stdio.h>

int main(){
	char linha[1024];
	int n;
	while((n=readln(0,linha,sizeof(linha)-1))){
		linha[n]='\0';
		printf("%d, %s\n",n,linha);
	}
	return 0;
}

#endif
