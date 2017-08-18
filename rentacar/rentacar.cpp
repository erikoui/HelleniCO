
#include<stdio.h>
#include<vector>
#include<iostream>
#include<math.h>
using namespace std;
typedef struct period{
	int a,t;
};

int globmax;

void quickSort(vector<period> &comp, int left, int right){    
	int i=left, j=right;    
	int pivot = comp[(i+j)/2].a;    

	// partition    
	while (i <= j) {  

		while (comp[i].a < pivot)    
			i++;    

		while (comp[j].a > pivot)    
			j--;    

		if (i <= j) {    
			int temp;  
			temp = comp[i].a;             // swap elements  
			comp[i].a = comp[j].a;  
			comp[j].a = temp; 

			temp = comp[i].t;             // swap elements  
			comp[i].t = comp[j].t;  
			comp[j].t = temp; 
			i++;    
			j--;    
		}	   
	}    

	// recursion    
	if (left < j)    
		quickSort(comp, left, j);    

	if (i < right)    
		quickSort(comp, i, right);    
}    

void calc(int n,int currcust,int counter,vector<period>& p){
	int max=0,j,i;//j=testcust
	int min;
	if(counter>globmax)
		globmax=counter;
	if(currcust==n)
		return;
	for(j=currcust+1;j<n;j++){//find the first possible customer
		if(p[j].a>=p[currcust].t){
			break;
		}
	}
	i=j;
	min=i;
	while((i<n)){
		if(p[i].t<p[min].t){
			min=i;
		}
		i++;
	}
	calc(n,min,counter+1,p);
}

int main(){
	freopen("rentacar.in","r",stdin);

	vector<period> p;
	globmax=0;
	int n;
	int min;
	cin>>n;
	vector<bool> mark;
	p.resize(n);
	mark.resize(n);
	int i,temp;
	for(i=0;i<n;i++){
		mark[i]=false;
		cin>>temp>>temp;
		p[i].a=temp;
		cin>>temp;
		p[i].t=temp;
	}
	int j;
	quickSort(p,0,n-1);

	for(i=0;i<n-1;i++){
	/*	float karroto=n;
		if(i%(int)floor((karroto/100))==0){
			float patata=i;
			printf("%.2f\n",patata/n*100);
		}*/
		calc(n,i,0,p);
	}
	n=globmax;
	freopen("rentacar.out","w",stdout);
	cout<<n;
}

