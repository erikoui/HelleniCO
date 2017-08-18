#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool gr(int a,int b){
    return a>b;
}

int main(){
	ifstream fin("tennis.in");
    ofstream fout("tennis.out");
    
    bool ret;
    int i,j,nlines,nath;
    vector<int> data,bdata;
    ret=false;
    int sum1=0;

    
    fin>>nlines;
    for(i=0;i<nlines;i++){
        //init vars
        ret=true;
        sum1=0;
        data.clear();
   
        //input and remove zeroes
        fin>>nath;
        data.resize(nath);
        for(j=0;j<nath;j++){
            fin>>data[j];
            if(data[j]==0){
                j--;
                nath--;
            }
        }
        data.resize(nath);
        
        //check if sum is odd
        for(j=0;j<nath;j++){sum1+=data[j];}
        
        if((sum1%2==1)||(nath==1)){
            ret=false;
        }
        else{
            sort(data.begin(),data.end(),gr);
            while(data[0]!=0){
                if(data[0]>=nath){
                    ret=false;
                    break;
                }
                for(j=1;j<data[0]+1;j++){
                    if(--data[j]==0){
                        nath--;
                    }
                }
                data[0]=0;
                nath--;
                sort(data.begin(),data.end(),gr);
            }
            
        }
        //print result
        ret?fout<<"Possible"<<endl:fout<<"Not possible"<<endl;
    }
    //done
    fin.close();
    fout.close();
    return 0;
}
