#include <stdio.h>
#include <stdlib.h>

FILE* out;
void qubits(int n,char a,char b,char c){
	if(n==1){
		fprintf(out,"%c %c\n",a,b);
	}else{
		qubits(n-1,a,c,b);
		fprintf(out,"%c %c\n",a,b);
		qubits(n-1,c,b,a);
	}
}

int main(){
	int n;
	FILE* in=fopen("qubits.in","r");
	out=fopen("qubits.out","w");
	fscanf(in,"%d",&n);
	qubits(n,'A','C','B');
	fclose(in);
	fclose(out);
	return 0;
}
