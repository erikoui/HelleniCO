#include <stdio.h>
#include <stdlib.h>
#include <cmath>
bool isPrime(int n){
	int i,r;
	r=(int)floor(sqrt((double)n));
	for(i=3;i<=r;i+=2){
		if(n%i==0){
			return false;
			break;
		}
	}
	return true;
}
int main(){
	FILE* in=fopen("goldbach.in","r");
	FILE* out=fopen("goldbach.out","w");
	int zigos;
	bool end=false;
	fscanf(in,"%d",&zigos);
	int i,j;
	for(i=3;(i<zigos)&&(!(end));i+=2){
		j=zigos-i;
		if((isPrime(i))&&(isPrime(j))){
			if(i+j==zigos){
				fprintf(out,"%d %d\n",i,j);
				end=true;
				break;
			}
			if(i+j>zigos){
				break;
			}
		}
	}
	fclose (in);
	fclose (out);
	return 0;
}
