#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include <algorithm>
#include<string>
using namespace std;

bool testonoff(int ls[],int on[],int off[],int numon,int numoff){
	int i,j;
	for(i=0;i<numon;i++){
		if(ls[on[i]-1]==-1){
			return false;
		}
	}
	for(i=0;i<numoff;i++){
		if(ls[off[i]-1]==1){
			return false;
		}
	}
	return true;
}

void press1(int ls[],int lamps){
	int i;
	for(i=0;i<lamps;i++){
		ls[i]=-ls[i];
	}
}

void press2(int ls[],int lamps){
	int i;
	for(i=0;i<lamps;i+=2){
		ls[i]=-ls[i];
	}
}

void press3(int ls[],int lamps){
	int i;
	for(i=1;i<lamps;i+=2){
		ls[i]=-ls[i];
	}
}

void press4(int ls[],int lamps){
	int i;
	for(i=0;i<lamps;i+=3){
		ls[i]=-ls[i];
	}
}

void next_enumeration(int a[],int i,int c){
	if(i<c){
		if(a[i]==4){
			a[i]=1;
			next_enumeration(a,i+1,c);
		}else{
			a[i]++;
		}
	}
}

void add_solution(int ls[],int lamps,string sol[],int solpos){
	int i;
	sol[solpos].clear();
	for(i=0;i<lamps;i++){
		if(ls[i]==1){
			sol[solpos].append("1");
		}else{
			sol[solpos].append("0");
		}
	}
}

void next_enumeration_x(int a[],int i){  
	if(i<4){  
		if(a[i]==1){  
			a[i]=0;  
			next_enumeration_x(a,i+1);  
		}else{  
			a[i]=1;  
		}  
	}  
}  


int main(){
	int lamps,counter;
	int on[20],off[20],numon,numoff;
	int state[100];//1=on,-1=off
	string solutions[272];
	int sworder[4];
	int j,k;
	int c=0;
	int numofsolutions=0;
	int temp;
	int i=0;
	for(i=0;i<100;i++){
		state[i]=1;
	}
	for(i=0;i<4;i++){
		sworder[i]=1;
	}
	freopen("lamps.in","r",stdin);
	freopen("lamps.out","w",stdout);
	cin>>lamps;
	cin>>counter;
	i=0;
	cin>>temp;
	while(temp!=-1){
		on[i]=temp;
		i++;
		cin>>temp;
	}
	numon=i;
	cin>>temp;
	i=0;
	while(temp!=-1){
		off[i]=temp;
		i++;
		cin>>temp;
	}
	numoff=i;
	///////////////////////////////////////////
	if(counter<4){
	for(i=0;i<56;i++){
		next_enumeration(sworder,0,counter);
		for(j=0;j<counter;j++){
			if(sworder[j]==1){
				press1(state,lamps);
			}else if(sworder[j]==3){
				press3(state,lamps);
			}else if(sworder[j]==2){
				press2(state,lamps);
			}else if(sworder[j]==4){
				press4(state,lamps);
			}
		}
		if((testonoff(state,on,off,numon,numoff))){
			add_solution(state,lamps,solutions,numofsolutions);
			numofsolutions++;
		}
		for(k=0;k<100;k++){
			state[k]=1;
		}
	}
	int nsol=0;
	for(i=0;i<numofsolutions;i++){
		for(j=0;j<numofsolutions;j++){
			if((solutions[i]==solutions[j])&&(i!=j)){
				solutions[j].clear();
			}
		}
	}
	for(i=0;i<numofsolutions;i++){
		if(solutions[i].length()>1){
			nsol++;
		}
	}

	numofsolutions=nsol;
	}

	///////////////////////////////////////////////

	for(i=0;i<4;i++){
		sworder[i]=0;
	}
	for(k=0;k<100;k++){
		state[k]=1;
	}

	for(i=0;i<16;i++){  
		next_enumeration_x(sworder,0);  
		c=0;  
		for(j=0;j<4;j++){  
			if(sworder[j]==1){  
				c++;  
			}  
		}  
		if((c==counter)||(counter>=4)){  
			for(j=0;j<4;j++){  
				if(sworder[j]==1){  
					if(j==0){  
						press1(state,lamps);  
					}  
					if(j==1){  
						press2(state,lamps);  
					}  
					if(j==2){  
						press3(state,lamps);  
					}  
					if(j==3){  
						press4(state,lamps);  
					}  
				}  
			}  
			if((testonoff(state,on,off,numon,numoff))){  
				add_solution(state,lamps,solutions,numofsolutions);  
				numofsolutions++;  
			}  
			for(k=0;k<100;k++){  
				state[k]=1;  
			}  
		}  
	}  

	for(i=0;i<numofsolutions;i++){
		for(j=0;j<numofsolutions;j++){
			if((solutions[i]==solutions[j])&&(i!=j)){
				solutions[j].clear();
			}
		}
	}
	sort(solutions,solutions+numofsolutions);
	for(i=0;i<numofsolutions;i++){
		if(solutions[i].length()>1){
			cout<<solutions[i]<<endl;
		}
	}
}
