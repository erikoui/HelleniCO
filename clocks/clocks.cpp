#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<string>
#include<iostream>;
#include<math.h>
using namespace std;

void next_enum(int s[],int i,int l){
	if(i<l){
		if(s[i]==3){
			s[i]=0;
			next_enum(s,i+1,l);
		}else{
			s[i]++;
		}
	}
}

bool test(int a,int b,int c,int d,int e,int f,int g,int h,int i){
	if((a%4==0)&&
		(b%4==0)&&
		(c%4==0)&&
		(d%4==0)&&
		(e%4==0)&&
		(f%4==0)&&
		(g%4==0)&&
		(h%4==0)&&
		(i%4==0)){
			return true;
	}return false;
}

int main(){
	freopen("clocks.in","r",stdin);
	freopen("clocks.out","w",stdout);
	int i;
	char sol[10];
	int clocka;
	int clockb;
	int clockc;
	int clockd;
	int clocke;
	int clockf;
	int clockg;
	int clockh;
	int clocki;

	int clocka_;
	int clockb_;
	int clockc_;
	int clockd_;
	int clocke_;
	int clockf_;
	int clockg_;
	int clockh_;
	int clocki_;

	int j;
	cin>>clocka>>clockb>>clockc>>clockd>>clocke>>clockf>>clockg>>clockh>>clocki;

	clocka_=clocka;
	clockb_=clockb;
	clockc_=clockc;
	clockd_=clockd;
	clocke_=clocke;
	clockf_=clockf;
	clockg_=clockg;
	clockh_=clockh;
	clocki_=clocki;

	int z=0;
	int cst;//counter
	int seq[]={0,0,0,0,0,0,0,0,0};
	int num=1;
	int lim=9;
	for(num=1;num<=lim;num++){
		for(j=1;j<=pow((double)4,num);j++){
			for(i=0;i<num;i++){
				for(cst=0;cst<seq[i];cst++){
					if(i==0){clocka++;clockb++;clockd++;clocke++;}
					else if(i==1){clocka++;clockb++;clockc++;}
					else if(i==2){clockb++;clockc++;clocke++;clockf++;}
					else if(i==3){clocka++;clockd++;clockg++;}
					else if(i==4){clockb++;clockd++;clocke++;clockf++;clockh++;}
					else if(i==5){clockc++;clockf++;clocki++;}
					else if(i==6){clockd++;clocke++;clockg++;clockh++;}
					else if(i==7){clockg++;clockh++;clocki++;}
					else if(i==8){clocke++;clockf++;clockh++;clocki++;}
				}
			}
			if(test(clocka,clockb,clockc,clockd,clocke,clockf,clockg,clockh,clocki)){
				int csst=0;
				for(cst=0;cst<num;cst++){
					if(seq[cst]!=0){
						if(seq[cst]==1){
							sol[csst]=cst+49;
							csst++;
						}
						if(seq[cst]==2){
							sol[csst]=cst+49;
							csst++;
							sol[csst]=cst+49;
							csst++;
						}
						if(seq[cst]==3){
							sol[csst]=cst+49;
							csst++;
							sol[csst]=cst+49;
							csst++;
							sol[csst]=cst+49;
							csst++;
						}
					}
				}

				sort(sol,sol+csst);
				for(cst=0;cst<csst;cst++){
					printf("%c ",sol[cst]);
				}
				exit(0);
			}

			clocka=clocka_;
			clockb=clockb_;
			clockc=clockc_;
			clockd=clockd_;
			clocke=clocke_;
			clockf=clockf_;
			clockg=clockg_;
			clockh=clockh_;
			clocki=clocki_;

			next_enum(seq,0,num);
		}
	}
	
}