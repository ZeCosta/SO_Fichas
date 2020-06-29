#include <stdio.h>
#include "g0.h"

#define SIZE 100
int v[SIZE];

int main(){
	int n;
	fill(v,SIZE,10);
	n=find(v,SIZE,1);
	n>=0?printf("encontrei em %d\n",n):printf("nao encontrei\n");
	fill(v+4,2,15);
	pprint(v,SIZE);	

	return 0;
}