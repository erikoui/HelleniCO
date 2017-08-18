#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main(){  
	FILE *fin,*fout;  
	int num,s,t,b=0,m=0,bo;  
	float el;  
	fin= fopen("downloads.in","r");  
	fout= fopen("downloads.out","w");  
	fscanf(fin,"%d",&num);  
	while (num>0){   
	    fscanf(fin,"%d %d",&s,&t);  
	    b+=s;  
	    m+=(s*t);  
	    num--;  
	}  
	el=round((float)m/b);  
	bo= (int)el;  
	fprintf(fout,"%d",bo);  
	fprintf(fout,"\n");  
	fclose(fin);  
	fclose(fout);  
	return 0;  
}  
