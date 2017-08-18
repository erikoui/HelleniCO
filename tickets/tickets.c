#include <stdio.h>
#include <stdlib.h>

int main(){
    int minpr=99999999;
    int n,i;
    int price;
    int a=0,b=0,c=0,d=0;
    FILE *in=fopen("tickets.in","r");
    FILE *out=fopen("tickets.out","w");
    fscanf(in,"%d%d%d%d%d",&n,&a,&b,&c,&d);
    for(i=n;i<=d*d;i++){
        if(i<a){
            price=i*10;
        }
        if(i>=a){
            price=i*9;
        }
        if(i>=b){
            price=i*8;
        }
        if(i>=c){
            price=i*7;
        }
        if(i>=d){
            price=i*5;
        }
        if(price<=minpr){
            minpr=price;
        }
    }
    fprintf(out,"%d\n",minpr);
    fclose(in);
    fclose(out);
    return 0;
}
        
    

