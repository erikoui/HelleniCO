#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;

int main(){
	freopen("nered.in","r",stdin);
	freopen("nered.out","w",stdout);
	int size,cubes;
	int positions[100][100];
	int factors[10000];
	cin>>size>>cubes;
	int i,j,x,y,a,b;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			positions[i][j]=0;
		}
	}
	for(i=0;i<cubes;i++){
		cin>>x>>y;
		positions[x-1][y-1]++;
	}
	int numfac=0;
	for(i=1;i<=cubes;i++){
		if(cubes%i==0){
			factors[numfac]=i;
			numfac++;
		}
	}
	int incountx,incounty;
	int countcubes=0,maxa=-1,maxb=-1,maxx=-1,maxy=-1,maxcubes=-1;
	for(i=0;i<numfac;i++){
		a=factors[i];//rect.x
		b=cubes/factors[i];//rect.y
		for(x=0;x<=size-a;x++){
			for(y=0;y<=size-b;y++){
				for(incountx=x;incountx<x+a;incountx++){
					for(incounty=y;incounty<y+b;incounty++){
						if(positions[incountx][incounty]!=0){
							countcubes++;
						}
					}
				}
				if(countcubes>maxcubes){//store which rect. has max bloxx
					maxcubes=countcubes;
					maxa=a;
					maxb=b;
					maxx=x;
					maxy=y;
				}
				countcubes=0;
			}
		}
	}
	int count=0;
	for(i=maxx;i<maxx+maxa;i++){
		for(j=maxy;j<maxy+maxb;j++){
			if(positions[i][j]==0){
				count++;
			}
		}
	}
	cout<<count<<endl;
	return 0;
}
