#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char fake[1000][20];
void minword(char* word,int num){
	const int s=strlen(word);
	char *f8k,*min;
	f8k=(char*)malloc(s);
	min=(char*)malloc(s);
	for(int j=0;j<s;j++){
		f8k[j]=word[j];
		min[j]=100;
	}
	for(int n=0;n<s;n++){
		char temp=f8k[0];//scramble goes until...
		for(int i=0;i<s-1;i++){
			f8k[i]=f8k[i+1];
		}
		f8k[s-1]=temp;//////...here
		if(strcmp(f8k,min)<0){//if new less than previous
			for(int j=0;j<s;j++){
				min[j]=f8k[j];//minimum=fake
			}
		}

	}
	for(int j=0;j<s;j++){
		fake[num][j]=min[j];//minimum=fake
	}
}

int main(){
	FILE* in=fopen("names.in","r");
	FILE* out=fopen("names.out","w");
	int names;
	fscanf(in,"%d",&names);
	char real[1000][20];
	int i;
	for(i=0;i<names;i++){
		fscanf(in,"%s",real[i]);
		minword(real[i],i);
	}
	int min=0;
	for(i=0;i<names-1;i++){
		if(strcmp(fake[min],fake[i+1])>0){
			min=i+1;
		}
	}
	fprintf(out,"%s\n",real[min]);
	fclose(in);
	fclose(out);
	return 0;
}
