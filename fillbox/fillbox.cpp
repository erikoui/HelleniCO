#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<algorithm>
#include<stdint.h>

using namespace std;

uint64_t countshit(uint64_t maxcube,uint64_t l,uint64_t w,uint64_t h){
	uint64_t sum=0;
	if(l==0){
		return 0;
	}if(w==0){
		return 0;
	}if(h==0){
		return 0;
	}
	if(l==1){
		return w*h;
	}if(w==1){
		return l*h;
	}if(h==1){
		return w*l;
	}
	if(maxcube==0){
		return 0;
	}
	if(maxcube!=1){
		uint64_t lenthleft=l%maxcube;
		uint64_t heitleft=h%maxcube;
		uint64_t withleft=w%maxcube;
		uint64_t mult=1;

		mult*=l/maxcube;
		sum+=countshit(maxcube/2,lenthleft,w,h);
		
		mult*=w/maxcube;
		sum+=countshit(maxcube/2,l-lenthleft,withleft,h);
		
		mult*=h/maxcube;
		sum+=countshit(maxcube/2,l-lenthleft,w-withleft,heitleft);

		sum+=mult;
	}
	return sum;
}

int main(){
	freopen("fillbox.in","r",stdin);
	freopen("fillbox.out","w",stdout);

	uint64_t W,H,L;
	cin>>L>>W>>H;
	uint64_t mindim=min(L,min(H,W));
	uint64_t i;
	for(i=0;i<100;i++){
		if(pow(2,(double)i)>mindim){
			mindim=pow(2,(double)i-1);
			break;
		}
	}
	
	cout<<countshit(524288,L,W,H);
	return 0;
}
