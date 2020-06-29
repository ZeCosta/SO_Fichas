#include <stdio.h>

void fill(int*vector, int size, int value){
	int i;
	for (i = 0; i < size; ++i){
		vector[i]=value;
	}
}

int find(int*vector, int size, int value){
	int i,check=-1;
	for (i = 0; i < size && check<0; ++i){
		if (vector[i]==value)check=i;
	}
	return check;
}

void pprint(int*vector, int size){
	int i;
	for (i = 0; i < size; ++i){
		printf("%d\n", vector[i]);
	}
}
