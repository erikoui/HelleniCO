
#include<stdio.h>
#include<stdlib.h>
#include <algorithm>
using namespace std;

typedef struct rock{
	int mass,volume;
	double density;
}rock;

bool density_desc(const rock& a, const rock& b){
    return a.density > b.density;
}

int main(){
	int numofrocks,maxvolume,i,j,totalrocks;
	bool flag = true;
	double finalmass,finalvolume;
	FILE* in=fopen("stones.in","r");
	FILE* out=fopen("stones.out","w");
	fscanf(in,"%d%d",&numofrocks,&maxvolume);
	rock *rocks=new rock[numofrocks];

	for(i=0;i<numofrocks;i++){
		fscanf(in,"%d%d",&rocks[i].volume,&rocks[i].mass);
		rocks[i].density=(double)rocks[i].mass/rocks[i].volume;
	}

	
	sort(rocks,rocks+numofrocks,density_desc);
	//for(i = 1; (i <= numofrocks) && flag; i++){
	//	flag = false;
	//	for (j=0; j < (numofrocks -1); j++){  
	//		if (rocks[j+1].density > rocks[j].density){ 
	//			double tempd=rocks[j].density;
	//			rocks[j].density=rocks[j+1].density;
	//			rocks[j+1].density=tempd;

	//			int tempi=rocks[j].mass;
	//			rocks[j].mass=rocks[j+1].mass;
	//			rocks[j+1].mass=tempi;

	//			tempi=rocks[j].density;
	//			rocks[j].volume=rocks[j+1].volume;
	//			rocks[j+1].volume=tempi;
	//			flag=true;
	//		}
	//	}
	//}

	i=-1;
	finalvolume=0;
	finalmass=0;
	while((i<numofrocks)&&(finalvolume<maxvolume)){
		i++;
		finalvolume+=rocks[i].volume;
	}
	totalrocks=i;
	finalvolume-=rocks[i].volume;
	for(i=0;i<totalrocks;i++){
		finalmass+=rocks[i].mass;
	}
	int remainingvolume=maxvolume-finalvolume;
	double addedmass=(double)remainingvolume*rocks[totalrocks].density;

	finalmass+=addedmass;
	fprintf(out,"%.3f",finalmass);
	fclose(in);
	fclose(out);
	return 0;
}
