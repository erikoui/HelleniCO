#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

int main(){
	char originalstr[1000];
	char repeatstr[1000];
	int lenth,maxperiod,currentperiod,j,k,l,start=0,swaps,minswaps=1001;//cannot be more than 1000 because cannot be more than 1000
	FILE *fin,*fout;      
	int first,last;
	char twochars[2];
	int i;
	int repeat_start;
	char originalrepeat[1000];
	fin= fopen("dna.in","r");      
	fout= fopen("dna.out","w");      
	fscanf(fin,"%d%d",&lenth,&maxperiod);      
	fscanf(fin,"%s",originalstr);        
	minswaps=999999;
	int a,c,t,g;
	a=0;
	c=0;
	t=0;
	g=0;
	swaps=0;
	repeatstr[0]='A';
	for(currentperiod=1;currentperiod<=maxperiod;currentperiod++){

		for(j=0;j<currentperiod;j++){
			for(i=j;i<lenth;i+=currentperiod){
				if(originalstr[i]=='A'){
					a++;
				}else if(originalstr[i]=='C'){
					c++;
				}else if(originalstr[i]=='T'){
					t++;
				}else{
					g++;
				}
			}
			if(max(max(a,c),max(t,g))==a){
				repeatstr[j]='A';
			}else if(max(max(a,c),max(t,g))==c){
				repeatstr[j]='C';
			}else if(max(max(a,c),max(t,g))==t){
				repeatstr[j]='T';
			}else if(max(max(a,c),max(t,g))==g){
				repeatstr[j]='G';
			}
			a=0;
		c=0;
		t=0;
		g=0;
		}
		
		swaps=0;
		for(l=0;l<lenth;l++){//count swaps
			if(repeatstr[l%currentperiod]!=originalstr[l]){
				swaps++;
			}
			if (swaps>=minswaps){
				break;
			}
		}
		minswaps=swaps;
	}
	fprintf(fout,"%d\n",minswaps); 
	return 0;      
}      
