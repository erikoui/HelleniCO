#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int main(){
    FILE* in=fopen("acropolis.in","r");
    FILE* out=fopen("acropolis.out","w");

    int onepl[1000];
    int no1s[1000];
    int n,k=0,l=0,i,j;
    int temp;

    fscanf(in,"%d",&n);
    for(i=0;i<n;i++){
        fscanf(in,"%d",&temp);
        if(temp==1){
            onepl[k]=i;
            k++;
        }
        else{
            no1s[l]=temp;
            l++;
        }
    }

    sort(no1s,no1s+l);

    k=0;
    l=0;
    for(i=0;i<n;i++){
        if(i!=onepl[k]){
            fprintf(out,"%i\n",no1s[l]);
            l++;
        }
        else{
            fprintf(out,"1\n");
            k++;
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}
