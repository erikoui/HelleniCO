//solves maintain problem using minimum spanning tree.
//#include <vector>
//#include <fstream>
//#include <map>
//#include <unordered_set>
//using namespace std;
//
//struct node{
//    map<int,int> connw;
//    vector<int> conns;
//    vector<int> weights;
//    int mindist;
//    
//};
//
//void initGraph(vector<node>& g, int N){
//    int i;
//    
//    g.resize(N);
//    for(i=0;i<N;i++){
//        g[i].mindist=99999;
//    }
//}
//
//bool notConnected(vector<node> g,int c,int& count,vector<bool>& v){
//    ++count;
//    v[c]=true;
//    for(map<int,int>::iterator i=g[c].connw.begin();i!=g[c].connw.end();i++){
//        if(!v[i->first]){
//            if(notConnected(g,i->first,count,v)){
//                return true;
//            }
//        }
//    }
//    int j;
//    c=0;
//    for(j=0;j<v.size();j++){
//        if(v[j]){
//            c++;
//        }
//    }
//    return c!=g.size();
//
//}
//TODO: find minimum spanning tree size function
//
//int getMinSpanningTreeLength(vector<node> g){
//    vector<int> next_nodes;
//    int count=0;
//    vector<bool>v;
//    v.resize(g.size());
//    if(notConnected(g,0,count,v)){
//        return -1;
//    }
//    else{
//        unordered_set<int> next_nodes;
//        vector<node> mst;
//        next_nodes.insert(0);put the first node in next_nodes
//        int i,min=9999;
//        unordered_set<int>::iterator min_index;
//        int sum=0;
//        
//        while(mst.size()<g.size()){
//            min=100000;
//            min_index=next_nodes.begin();
//            for(unordered_set<int>::iterator ti=next_nodes.begin();ti!=next_nodes.end();ti++){for all nodes in question find the one with mindist
//                if(g[*ti].mindist<min){
//                    min=g[*ti].mindist;
//                    min_index=ti;
//                }
//            }
//            mst.push_back(g[*min_index]);
//            for all nodes connected to min node update their mindist
//            for(map<int,int>::iterator it=g[*min_index].connw.begin();it!=g[*min_index].connw.end();it++){
//                if(g[it->first].mindist>it->second){
//                    g[it->first].mindist=it->second;
//                    next_nodes.insert(it->first);
//                }
//            }
//            next_nodes.erase(min_index);
//        }
//        
//        for(i=0;i<mst.size();i++){
//            sum+=mst[i].mindist;
//        }
//        return sum;
//        
//    }
//}
//
//int main(){
//    vector<node> G,mst,notmst;
//    vector<bool> V;visited
//    uint32_t N,W;
//    int i,a,b,c;
//    int test;
//    ifstream fin("maintain.in");
//    ofstream fout("maintain.out");
//    
//    fin>> N >> W;
//    initGraph(G,N);
//    V.resize(N);
//    
//    for(i=0;i<W;i++){
//        V.clear();
//        V.resize(N);
//        fin>>a>>b>>c;
//        --a;
//        --b;
//        test=G[a].connw.size();
//        if(G[a].connw.count(b)==1){
//            if(c<G[a].connw.at(b)){
//                G[a].connw[b]=c;
//            }
//        }else{
//            G[a].connw[b]=c;
//        }
//              test=G[a].connw.size();
//        if(G[b].connw.count(a)==1){exists
//            if(c<G[b].connw.at(a)){
//                G[b].connw[a]=c;
//            }
//        }else{
//            G[b].connw[a]=c;
//        }
//
//        a=0;
//        G[0].mindist=0;
//        fout<<getMinSpanningTreeLength(G)<<endl;
//    }
//    
//    return 0;
//}
