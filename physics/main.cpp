#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct triplet{
    int cont[3];
    bool deleted;
};

bool lessthan(triplet t,triplet u){
    return t.cont[0]<u.cont[0];
}

void deel(vector<triplet>& data,vector<int>& str1,vector<int>& str2,int i){
    if(!data[i].deleted){//not already deleted
        data[i].deleted=true;
        str1[data[i].cont[1]-1]--;//reduce the repeats by one
        str2[data[i].cont[2]-1]--;
        if(str1[data[i].cont[1]-1]==0){//repeats gone to zero
            deel(data,str1,str2,data[i].cont[1]-1);//delete that too
        }
        if(str2[data[i].cont[2]-1]==0){
            deel(data,str1,str2,data[i].cont[2]-1);
        }
    }
}
    
int main(int argc, char **argv){
    int i,n,count=0;
    vector<triplet> data;
    triplet buffer;
    ifstream fin("physics.in");
    
    fin>>n;
    data.reserve(n);
    buffer.deleted=false;
    
    for(i=0;i<n;i++){
        fin>>buffer.cont[0];
        data.push_back(buffer);
    }
    for(i=0;i<n;i++){
        buffer=data[i];
        fin>>buffer.cont[1];
        data[i]=buffer;
    }
    for(i=0;i<n;i++){
        buffer=data[i];
        fin>>buffer.cont[2];
        data[i]=buffer;
    }
    
    //sort using first array
    sort(data.begin(),data.end(),lessthan);
    
    vector<int> str1,str2;//contains the number of times a number repeats in the row(index is the number, contents is the repeats)
    str1.resize(n);
    str2.resize(n);
    
    for(i=0;i<n;i++){//find str
        str1[data[i].cont[1]-1]++;
        str2[data[i].cont[2]-1]++;
    }
    for(i=0;i<n;i++){//check if zero repeats
        if(str1[i]==0){//num missing
            deel(data,str1,str2,i);//delete recursively
        }
        if(str2[i]==0){//num missing
            deel(data,str1,str2,i);
        }
    }
    for(i=0;i<n;i++){
        if(data[i].deleted){
            count++;
        }
    }

    ofstream fout("physics.out");
    fout<<count<<endl;
    fout.close();
    fin.close();
}
