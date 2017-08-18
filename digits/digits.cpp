#include<stdio.h>
#include<stdlib.h>
#include <algorithm>
#include <math.h>
using namespace std;

void get_digits(long num,int digits[],int &size){
	int i=0;
	int temp[10];
	while(num>0){
		temp[i] = num % 10;
		num = num / 10;
		i++;
	}
	size=i;
	int k=0;
	for(i=i-1;i>=0;i--){
		digits[k]=temp[i];
		k++;
	}	
}

void set_remaining_digits(long num,int rem[],int &size){
	int d[10];
	int s,k=0;

	get_digits(num,d,s);

	int i;
	for(i=0;i<s;i++){if(d[i]==1){break;}}if(i==s){rem[k]=1;k++;}
	for(i=0;i<s;i++){if(d[i]==2){break;}}if(i==s){rem[k]=2;k++;}
	for(i=0;i<s;i++){if(d[i]==3){break;}}if(i==s){rem[k]=3;k++;}
	for(i=0;i<s;i++){if(d[i]==4){break;}}if(i==s){rem[k]=4;k++;}
	for(i=0;i<s;i++){if(d[i]==5){break;}}if(i==s){rem[k]=5;k++;}
	for(i=0;i<s;i++){if(d[i]==6){break;}}if(i==s){rem[k]=6;k++;}
	for(i=0;i<s;i++){if(d[i]==7){break;}}if(i==s){rem[k]=7;k++;}
	for(i=0;i<s;i++){if(d[i]==8){break;}}if(i==s){rem[k]=8;k++;}
	for(i=0;i<s;i++){if(d[i]==9){break;}}if(i==s){rem[k]=9;k++;}
	size=9-s;
}

bool test_solution(int m,int m1,int m2){
	if(m*m1==m2){
		return true;
	}else{
		return false;
	}
}

int make_num(int digits[],int start,int end){
	int i;
	int ret=0;
	int mult=pow((double)10,(int)(end-start));
	for(i=start;i<=end;i++){
		ret+=digits[i]*mult;
		mult/=10;
	}
	return ret;
}

int make_m2(int digits[],int skipstart,int skip,int end){
	int i;
	int ret=0;
	int mult=pow((double)10,end-skip);
	for(i=0;i<=end;i++){
		if((i<skipstart)||(i>=skipstart+skip)){
			ret+=digits[i]*mult;
			mult/=10;
		}
	}
	return ret;
}



int main(){
	long m,m1,m2;
	int i,s,start,total,testsize,k;
	int dig[10];
	int solutions[2][5000];
	int max=1;
	freopen("digits.in","r",stdin);
	freopen("digits.out","w",stdout);

	scanf("%d",&m);
	set_remaining_digits(m,dig,s);
	prev_permutation(dig,dig+s);


	for(i=1;i<s;i++){
		max=max*i;
	}
	total=s*max;
	k=0;

	for(testsize=0;testsize<s;testsize++){
		for(i=0;i<total;i++){
			next_permutation(dig,dig+s);
			for(start=0;start<s-testsize;start++){
				m1=make_num(dig,start,start+testsize);
				m2=make_m2(dig,start,testsize+1,s-1);
				if(test_solution(m,m1,m2)){
					solutions[0][k]=m1;
					solutions[1][k]=m2;
					k++;
				}
			}
		}
	}
	if(k==0){
		printf("0\n");
	}else{
		sort(solutions[0],solutions[0]+k-1);
		printf("%d %d\n",solutions[0][0],solutions[1][0]);
	}
	return 0;
}
