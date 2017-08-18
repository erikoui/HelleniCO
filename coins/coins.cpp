#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

int main(){
    freopen("coins.in","r",stdin);
    
    vector<int> bacoins;
    vector<bool> addvec;
    vector<char> abba;
    int i,j,a,b,n;
    
    cin>>a>>b>>n;

    bacoins.resize(n);
    for (i=0;i<n;i++){
        cin>>bacoins[i];
    }
    sort(bacoins.begin(),bacoins.end());
    addvec.resize(bacoins[n-1]+1);
    addvec[0]=false;
    for(i=1;i<bacoins[n-1]+1;i++){
        if(i-b>=0){
            if((addvec[i-a]==false)||(addvec[i-b]==false)||(addvec[i-1]==false)){
                addvec[i]=true;
            }
        }else if(i-a>=0){
            if((addvec[i-a]==false)||(addvec[i-1]==false)){
                addvec[i]=true;
            }
        }
        else{
            if(addvec[i-1]==false){
                addvec[i]=true;
            }
        }
    }
    freopen("coins.out","w",stdout);
    for(i=0;i<n;i++){
        if(addvec[bacoins[i]]){
            cout<<'A';
        }else{
            cout<<'B';
        }
    }
    return 0;
}

