#include <stdio.h>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int main(int argc, char **argv){
	vector<vector<int> > tri;
    int i,j,levels;
    ifstream fin("numtri.in");
    ofstream fout("numtri.out");
    fin>>levels;
    tri.resize(levels);
    for(i=0;i<levels;i++){
        tri[i].resize(i+1);
        for(j=0;j<i+1;j++)
            fin>>tri[i][j];
    }
    for(i=levels-2;i>=0;i--)
        for(j=0;j<tri[i].size();j++)
            tri[i][j]+=max(tri[i+1][j],tri[i+1][j+1]);
    fout<<tri[0][0];
}

