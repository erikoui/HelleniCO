//solves maintain problem using minimum spanning tree.
#include <vector>
#include <fstream>
#include <map>
using namespace std;

struct node{
    map<int,int> connw;
    //vector<int> conns;
    //vector<int> weights;
    int mindist;
    
};

void initGraph(vector<node>& g, int N){
    int i;
    
    g.resize(N);
    for(i=0;i<N;i++){
        g[i].mindist=99999;
    }
}

bool isConnected(vector<node>& g, int N, vector<bool>& visited, int& nv, int j){
    //nv is num of visited nodes (instead of counting trues in visited)
    map<int,int>::iterator i;
    
    visited[j]=true;
    ++nv;
    
    if(nv==N){
        return true;
    }
    
    for(i=g[j].connw.begin();i!=g[j].connw.end();i++){
        if(!visited[i->first]){
            if(isConnected(g,N,visited,nv,i->first)){
                return true;
            }
        }
    }
    return false;
}

//TODO: find minimum spanning tree size function

int getMinSpanningTreeLength(vector<node> g){
    vector<int> next_nodes;
    vector<node> mst;
    next_nodes.push_back(0);//put the first node in next_nodes
    int i,min=9999,min_index=-1,sum=0;
    
    while(mst.size()<g.size()){
        min=100000;
        min_index=-1;
        for(i=0;i<next_nodes.size();i++){//for all nodes in question find the one with mindist
            if(g[next_nodes[i]].mindist<min){
                min=g[next_nodes[i]].mindist;
                min_index=i;
            }
        }
        mst.push_back(g[next_nodes[min_index]]);
        //for all nodes connected to min node update their mindist
        for(map<int,int>::iterator it=g[next_nodes[min_index]].connw.begin();it!=g[next_nodes[min_index]].connw.end();it++){
            if(g[it->first].mindist>it->second){
                g[it->first].mindist=it->second;
                next_nodes.push_back(it->first);
            }
        }
        next_nodes.erase(next_nodes.begin()+min_index);
    }
    
    for(i=0;i<mst.size();i++){
        sum+=mst[i].mindist;
    }
    return sum;
}

int main(){
    vector<node> G,mst,notmst;
    vector<bool> V;//visited
    uint32_t N,W;
    int i,a,b,c;
    int test;
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
        test=G[a].connw.size();
        if(G[a].connw.count(b)==1){
            if(c<G[a].connw.at(b)){
                G[a].connw[b]=c;
            }
        }else{
            G[a].connw[b]=c;
        }
              test=G[a].connw.size();
        if(G[b].connw.count(a)==1){//exists
            if(c<G[b].connw.at(a)){
                G[b].connw[a]=c;
            }
        }else{
            G[b].connw[a]=c;
        }

        a=0;
        if(isConnected(G,N,V,a,1)){
            G[0].mindist=0;
            fout<<getMinSpanningTreeLength(G)<<endl;
        }else{
            fout<<"-1"<<endl;
        }
    }
    
    return 0;
}
