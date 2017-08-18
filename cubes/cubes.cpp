#include <iostream>
#include <fstream>
using namespace std;

int main(){
	ifstream fin("cubes.in");
	ofstream fout("cubes.out");
	long boxes,step,height,i,j,add,counter;
	int heightlim[100000];

	heightlim[0]=1;
	counter=1;
	add=1;

	fin>>boxes;//read num of boxes
	fin>>step;//read max step

	for(i=1;i<100000;i++){
		heightlim[i]=heightlim[i-1]+add;
		counter++;
		if(counter==step){
			add++;
			counter=0;
		}
	}

	for(i=1;i<100000;i++){
		if((heightlim[i]>boxes)&&(heightlim[i-1]<boxes)){
			height=i;//+1-1
			break;
		}
	}
	fout<<height<<endl;
	return 0;
}
