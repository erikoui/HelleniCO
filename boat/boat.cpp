#include <stdio.h>
#include <string.h>
#include <stdio.h>
using namespace std;

char cars[1000][42];
int main(){
	FILE* in=fopen("boat.in","r");
	FILE* out=fopen("boat.out","w");
	int numports;
	fscanf(in,"%d",&numports);
	int k,i,leave,come,numcars=0;
	for(k=0;k<numports;k++){
		fscanf(in,"%d%d",&leave,&come);
		for(i=numcars;i>numcars-leave;i--){
			cars[i][0]='\0';
		}
		numcars-=leave;
		for(i=numcars;i<numcars+come;i++){
			fscanf(in,"%s",cars[i]);
		}
		numcars+=come;
	}
	int j;
	for(i=0;i<numcars;i++){//sort(very time consuming)
		for(j=1;j<=numcars;j++){
			if(strcmp(cars[j],cars[j-1])<0){
				char temp[42];
				int k;
				for(k=0;k<42;k++){
					temp[k]=cars[j][k];
					cars[j][k]=cars[j-1][k];
					cars[j-1][k]=temp[k];
				}
			}
		}
	}
	for(i=01;i<=numcars;i++){
		fprintf(out,"%s\n",cars[i]);
	}
	fclose(in);
	fclose(out);
	return 0;
}


