#include "hiddenlib.h"
#include <math.h>
#include <stdlib.h>
int main(){
	long boxxes,start=1;
	boxxes=getN();//get last item
	for(;;){
		if(compare(start,boxxes)==0){//box is exactly in middle
			ishidden((boxxes+start)/2);
			exit(0);
		}else if (compare(start,boxxes)==1){
			ishidden(start);
			boxxes=ceil((double)(boxxes+start)/2);
		}
		else{
			ishidden(boxxes);
			start=floor((double)(boxxes+start)/2);
		}
	}
	return 0;
}
