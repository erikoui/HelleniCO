//Simplified version of main.cpp

#include <vector>
#include <fstream>

using namespace std;

struct edge{
    int to,weight;
};

struct node{
    vector<edge> conns;
    int mindist;
};

int edgeExists(vector<node> g,int f,int t){//returns index of edge if it exists, else -1
    int i;
    for(i=0;i<g[f].conns.size();i++){
        if(g[f].conns[i].to==t){
            return i;
        }
    }
    return -1;
}

int getMinSpanningTreeLength(vector<node> g){
    
}

int main(){
    vector<node> G;
    edge edge_buffer;
    int numnodes,numedges;
    int i;
    int from,to,weight;

    ifstream fin("maintain.in");
    ofstream fout("maintain.out");
    fin >> numnodes >> numedges;
    
    G.resize(numnodes);
    for(i=0;i<numedges;i++){//for all lines in file (all new edges)
        fin>>from>>to>>weight;
        from--;
        to--;
        
        edge_buffer.to=to;
        edge_buffer.weight=weight;
        
        if(edgeExists(G,from,to)==-1){/*E[from,to] does not exist*/
            G[from].conns.push_back(edge_buffer);//add this edge to the graph
            edge_buffer.to=from;
            G[to].conns.push_back(edge_buffer);
        }
        else{//E[from,to] exists
            if(G[from].conns[edgeExists(G,from,to)].weight>weight){//existng weight is more than new weight
                G[from].conns[edgeExists(G,from,to)].weight=weight;//update with new weight
                edge_buffer.to=from;
                G[to].conns[edgeExists(G,to,from)].weight=weight;
            }//else leave as is
        }
        
        G[0].mindist=0;
        fout<<getMinSpanningTreeLength(G)<<endl;
    }
}