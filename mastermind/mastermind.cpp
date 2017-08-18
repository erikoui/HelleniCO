#include<stdio.h>    
#include<stdlib.h>    
#include<iostream>    
#include<vector>    
#include<math.h>    
#include<list>
#include <algorithm>  

using namespace std;    

typedef struct dt{    
	int n[5];    
	int color,place;    
}dt;    

void next_enumeration(int a[],int i,int limit,int sizeofa,bool repeating){//i starts always 0    
	if(repeating){    
		if(i<sizeofa){    
			if(a[i]==limit){    
				a[i]=1;    
				next_enumeration(a,i+1,limit,sizeofa,repeating);    
			}else{    
				a[i]++;    
			}    
		}    
	}    
	else{    
		bool re=false;    
		if(sizeofa>1){    
			while(!re){    
				re=false;    
				for(int x=0;x<sizeofa && !re;x++){    
					for(int y=0;y<sizeofa && !re;y++){    
						if(x!=y){    
							if(a[x]==a[y]){    
								re=true;    
							}    
						}    
					}    
				}    
				if(!re)    
					next_enumeration(a,i,limit,sizeofa,true);    
			}    
		}    
		else{    
			next_enumeration(a,i,limit,sizeofa,true);    
		}    
	}    
}    

bool testtt(dt correct,int trial[],int s){
	int c,p;
	c=0;//counts correct colors
	p=0;//counts correct positions
	int i;

	for(i=0; i<s; i++){
		if(correct.n[i]==trial[i]){
			p++;
			trial[i]='*';
			correct.n[i]='*';
		}
	}
	// check for a correct letter at a wrong position
	for(int corpos=0; corpos<s; corpos++){
		if(correct.n[corpos]=='*') continue;
		for(int trypos=0; trypos<s; trypos++){
			if(trial[trypos]!='*' && correct.n[corpos]==trial[trypos]){
				c++;
				trial[trypos]='*';
				correct.n[corpos]='*';
				break;
			}
		}
	}

	if((c!=correct.color)||(p!=correct.place)){    
		return false;    
	}else{    
		return true;    
	}    
}

bool testc(int s[],int sizeofs){
	int i;
	for(i=0;i<sizeofs;i++){
		if(s[i]!=1){
			return false;
		}
	}
	return true;
}

int main(){    
	freopen("mastermind.in","r",stdin);    
	freopen("mastermind.out","w",stdout);    

	int test[7];
	int i,j,k,l,m,solutions=0; 
	int counter;  
	int lines;//N>=1//num of lines(trials)    
	int num;//M<=10//num of different colors(per trial)    
	int snum;//3<=K<=5//size of trials(x y z = 3),(x y z u v = 5)    
	list<int> ans;
	vector<dt> data; 

	counter=0;    

	cin>>lines>>num>>snum;    
	data.resize(lines); 

	int *skip=new int[snum];
	for(int k=0;k<snum;k++){    
		skip[k]=1;    
	}

	for(i=0;i<lines;i++){    
		for(j=0;j<snum;j++){    
			cin>>data[i].n[j];    
		}    
		cin>>data[i].place>>data[i].color;    
	}    

	int *cpy=new int[snum];
	do{  
		for(j=0;j<lines;j++){  
			for(i=0;i<snum;i++){
				cpy[i]=skip[i];
			}

			if(!testtt(data[j],cpy,snum)){  
				break;  
			}  
		}if(j==lines){  
			counter++;	
		} 
		next_enumeration(skip,0,num,snum,true);  
	}while(!testc(skip,snum));

	cout<<counter;
}    
