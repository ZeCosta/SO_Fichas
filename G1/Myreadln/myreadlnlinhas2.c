#include <unistd.h>

int readc(int fd, char* c){
	static char line[1024];
	static int i=0,n=0;
	
	if(n==-1)return -1;
	if(i==n){
		n=read(fd,line,sizeof(line));
		i=0;
		if(n<=0)return n;
	}

	*c=line[i];
	i++;
	return 1;
}

int readln(int fd,char* line, size_t size){
	int i=0;
	int n;
	while(i!=size){
	       	if((n=readc(fd,line+i)==1))i++;
		else return i>0?i:n;
		if(line[i-1]=='\n')break;
	}
	return i;
}

#ifdef __TEST__
#include <stdio.h>
#include <string.h>
#include <assert.h>
int main(){
	char linha[1024],preambulo[10];
	int n;
	int nlinhas=0;
	while((n=readln(0,linha,sizeof(linha)-1))>0){
		linha[n]='\0';
		nlinhas++;
		sprintf(preambulo,"%8d  ",strlen(preambulo));
		assert(strlen(preambulo)==10);
		write(1,preambulo,strlen(preambulo));
		write(1,linha,n+1);

	}
	return 0;
}

#endif
