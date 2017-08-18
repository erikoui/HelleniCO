#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct edge{
    int to,weight;
};

struct node{
    vector<edge> in,out;
    int incount;
    int maxdist,mindist;
    int index;
    bool visited;
};

void topologicalSort(vector<node>& graph, uint32_t current_node,vector<node>& tpsortedgraph){
    uint32_t j;
    //save the curent node into the topologically sorted graph
    tpsortedgraph.push_back(graph[current_node]);
    graph[current_node].visited=true;
    
    //exit starement
    if(current_node==graph.size()-1){
        return;
    }
    
    //recursion
    //simulates the deletion of graph[current_node] by subtracting 1 from the (in counter) of the nodes it is connected to.
    //the recurs for each of those nodes whose incount has been changed to 0.
    for(j=0;j<graph[current_node].out.size();j++){
        --graph[graph[current_node].out[j].to].incount;
        //topologicalSort(graph,graph[current_node].out[j].to,tpsortedgraph);
    }
    for(j=0;j<graph.size();j++){
        if(graph[j].incount==0){
            if(!graph[j].visited)
                topologicalSort(graph,j,tpsortedgraph);
        }
    }
}

int main(int argc, char **argv)
{
    ifstream fin("troodos.in");
	ofstream fout("troodos.out");
    
    uint32_t num_nodes,num_edges;
    uint32_t i;
    uint32_t input_from,input_to,input_weight;
    uint32_t output_sub1,output_sub2,output_sub3;//max distance, sum(max-min)for each node, 3rd subproblem
    
    edge edge_buffer;
    vector<node> graph,tpsortedgraph;
    
    fin>>num_nodes>>num_edges;
    graph.resize(num_nodes);
    
    for(i=0;i<num_nodes;i++){
        graph[i].mindist=999999;
        graph[i].maxdist=0;
        graph[i].incount=0;
        graph[i].visited=false;
    }
    graph[0].mindist=0;
    
    for(i=0;i<num_edges;i++){
        fin>>input_from>>input_to>>input_weight;
        
        edge_buffer.to=input_to;
        edge_buffer.weight=input_weight;
        graph[input_from].out.push_back(edge_buffer);
        graph[input_from].index=input_from;
        
        edge_buffer.to=input_from;
        graph[input_to].in.push_back(edge_buffer);
        graph[input_to].index=input_to;
        graph[input_to].incount++;
    }
    
    topologicalSort(graph,0,tpsortedgraph);
 
    //TODO: sub1 is get max distance from 0 to n-1
    //TODO: sub2 is get sum of max(0 to i)-min(0 to i) for i=0 to n-1
    //TODO: sub3 is something weird which i have not thought about yet
 
    fin.close();
    fout.close();
	return 0;
}
