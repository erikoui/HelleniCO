#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>

using namespace std;

int main(){
    FILE* in=fopen("elevator.in","r");
    FILE* out=fopen("elevator.out","w");
    long dolphins;
    int weights[100000];
    int routes;
    int maxw8;//=weights[dolphins-1];
long patata;
    fscanf(in,"%d",&dolphins);
    int i;
    for(i=0;i<dolphins;i++){
        fscanf(in,"%d",&weights[i]);
    }
    
    routes=(int)ceil((float)dolphins/2);
    sort(weights,weights+dolphins);
    

    if(dolphins%2==1){
                      
        maxw8=weights[dolphins-1];
        patata=dolphins-2;
        for(i=0;i<patata;i++){
            if(weights[i]+weights[patata]>maxw8){
                maxw8=(weights[i]+weights[patata]);
            }
            patata--;
        }
    }else{
        patata=dolphins-2;
        maxw8=weights[dolphins-1]+weights[0];
        for(i=1;i<patata;i++){
            if(weights[i]+weights[patata]>maxw8){
                maxw8=(weights[i]+weights[patata]);
            }
            patata--;
        }
    }   
    fprintf(out,"%d %d",routes,maxw8);
}

