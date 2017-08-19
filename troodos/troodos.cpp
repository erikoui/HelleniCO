#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct edge {
    int to, weight;
};

struct node {
    vector<edge> in, out;
    int incount;
    int maxdist, mindist;
    int index;
    int maxpathpred;
    bool visited;
};

void topologicalSort (vector<node>& graph, uint32_t current_node, vector<node>& tpsortedgraph)
{
    uint32_t j;
    //save the curent node into the topologically sorted graph
    tpsortedgraph.push_back (graph[current_node]);
    graph[current_node].visited = true;

    //exit starement
    if (current_node == graph.size() - 1) {
        return;
    }

    //recursion
    //simulates the deletion of graph[current_node] by subtracting 1 from the (in counter) of the nodes it is connected to.
    //the recurs for each of those nodes whose incount has been changed to 0.
    for (j = 0; j < graph[current_node].out.size(); j++) {
        --graph[graph[current_node].out[j].to].incount;
        //topologicalSort(graph,graph[current_node].out[j].to,tpsortedgraph);
    }
    for (j = 0; j < graph.size(); j++) {
        if (graph[j].incount == 0) {
            if (!graph[j].visited)
                topologicalSort (graph, j, tpsortedgraph);
        }
    }
}

int main (int argc, char **argv)
{
    ifstream fin ("troodos.in");
    ofstream fout ("troodos.out");

    uint32_t num_nodes, num_edges;
    uint32_t i, j;
    uint32_t input_from, input_to, input_weight;
    uint32_t output_sub1, output_sub2, output_sub3; //max distance, sum(max-min)for each node, 3rd subproblem
    uint32_t maxdist_to_current = 0, index_of_current, index_of_previous, mindist_of_previous, mindist_to_current, maxdist_of_previous, weight_of_j_to_i, saved_index_of_previous;

    edge edge_buffer;
    vector<node> graph, tpsortedgraph;

    fin >> num_nodes >> num_edges;
    graph.resize (num_nodes);

    for (i = 0; i < num_nodes; i++) {
        graph[i].mindist = 999999;
        graph[i].maxdist = 0;
        graph[i].incount = 0;
        graph[i].visited = false;
        graph[i].maxpathpred = 0;
    }
    graph[0].mindist = 0;

    for (i = 0; i < num_edges; i++) {
        fin >> input_from >> input_to >> input_weight;

        edge_buffer.to = input_to;
        edge_buffer.weight = input_weight;
        graph[input_from].out.push_back (edge_buffer);
        graph[input_from].index = input_from;

        edge_buffer.to = input_from;
        graph[input_to].in.push_back (edge_buffer);
        graph[input_to].index = input_to;
        graph[input_to].incount++;
    }

    //O(n) topological sort
    topologicalSort (graph, 0, tpsortedgraph);

    //find max distance from 0 to n-1
    for (i = 1; i < tpsortedgraph.size(); i++) { //for all nodes in topological order
        //current maxdist is max(in[j].maxdist+weight)
        index_of_current = tpsortedgraph[i].index;
        maxdist_to_current = 0;
        for (j = 0; j < graph[index_of_current].in.size(); j++) { //for all nodes that lead to node i
            index_of_previous = graph[index_of_current].in[j].to;
            maxdist_of_previous = graph[index_of_previous].maxdist;
            weight_of_j_to_i = graph[index_of_current].in[j].weight;
            if (weight_of_j_to_i + maxdist_of_previous > maxdist_to_current) {
                maxdist_to_current = weight_of_j_to_i + maxdist_of_previous;
                saved_index_of_previous = index_of_previous;
            }
        }
        graph[tpsortedgraph[i].index].maxdist = maxdist_to_current;
        graph[tpsortedgraph[i].index].maxpathpred = saved_index_of_previous;//save the longest path
    }
    output_sub1 = graph[graph.size() - 1].maxdist; //save answer to subproblem 1

    //find min distance to next node by using maxdist as min distance of previous node
    for (i = 1; i < tpsortedgraph.size(); i++) { //for all nodes in topological order
        //current mindist is max(in[j].mindist+weight)
        index_of_current = tpsortedgraph[i].index;
        mindist_to_current = 999999;
        for (j = 0; j < graph[index_of_current].in.size(); j++) { //for all nodes that lead to node i
            index_of_previous = graph[index_of_current].in[j].to;
            mindist_of_previous = graph[index_of_previous].maxdist;
            weight_of_j_to_i = graph[index_of_current].in[j].weight;
            if (weight_of_j_to_i + mindist_of_previous < mindist_to_current) {
                mindist_to_current = weight_of_j_to_i + mindist_of_previous;
            }
        }
        graph[tpsortedgraph[i].index].mindist = mindist_to_current;
    }
    output_sub2 = 0;
    for (i = 0; i < graph.size(); i++) {
        output_sub2 += graph[i].maxdist - graph[i].mindist;
    }

    //sub3 is num of nodes - num of nodes in longest path

    //count num of nodes in longest path
    output_sub3 = 1;
    i = graph.size() - 1;
    while (i != 0) {
        output_sub3++;
        i = graph[i].maxpathpred;
    }
    output_sub3 = graph.size() - output_sub3;

    fout << output_sub1 << " " << output_sub2 << " " << output_sub3 << endl;
    fin.close();
    fout.close();
    return 0;
}
