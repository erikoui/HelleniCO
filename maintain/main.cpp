//solves maintain problem using minimum spanning tree.
#include <vector>
#include <fstream>

using namespace std;

struct node{
    vector<int> conns;
    vector<int> weights;
    int mindist;
    
};

void initGraph(vector<node>& g, int N){
    int i;
    
    g.resize(N);
    for(i=0;i<N;i++){
        g[i].mindist=99999;
    }
}

bool isConnected(vector<node>& g, int N, vector<bool>& visited, uint32_t& nv, int j){
    //nv is num of visited nodes (instead of counting trues in visited)
    uint32_t i;
    
    visited[j]=true;
    ++nv;
    
    if(nv==N){
        return true;
    }
    
    for(i=0;i<g[j].conns.size();i++){
        if(!visited[g[j].conns[i]]){
            if(isConnected(g,N,visited,nv,g[j].conns[i])){
                return true;
            }
        }
    }
    return false;
}

//TODO: find minimum spanning tree size function

int getMinSpanningTreeLength(vector<node>& g,int N,vector<int> mst,vector<int> not_in_mst,int curr){

}

int main(){
    vector<node> G,mst,notmst;
    vector<bool> V;//visited
    uint32_t N,W;
    uint32_t i,a,b,c;
    
    ifstream fin("maintain.in");
    ofstream fout("maintain.out");
    
    fin>> N >> W;
    initGraph(G,N);
    V.resize(N);
    
    for(i=0;i<W;i++){
        V.clear();
        V.resize(N);
        fin>>a>>b>>c;
        --a;
        --b;
        G[a].conns.push_back(b);
        G[a].weights.push_back(c);
        G[b].conns.push_back(a);
        G[b].weights.push_back(c); 
        a=0;
        if(isConnected(G,N,V,a,1)){
            fout<<getMinSpanningTreeLength(G,N,mst,notmst,0)<<endl;
        }else{
            fout<<"-1"<<endl;
        }
    }
    
    return 0;
}
