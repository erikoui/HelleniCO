#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef struct{
    int from, to, weight, visited;
}edge;

typedef struct{
    int n, dist;//id of node and distance from root
    bool used;
    vector<edge> edges;
}node;

int max(int a, int b){
    return a > b ? a : b;
}

bool not_in(vector<node> w, int n){
    for (int i = 0; i < w.size(); i++){
        if (w[i].n == n){
            return false;
        }
    }
    return true;
}

int main(){
    freopen("companies.in", "r", stdin);
    freopen("companies.out", "w", stdout);

    vector<node> graph;
    edge edge_buffer;
    vector<vector<int> > owns;//i owns j by value percent
    vector<vector<int> > temp_owns;//n by 2 table containing ownerships in current iteration
    vector<vector<int> > actual_owns;//n by 2 table containing all ownerships
    vector<int> actual_owns_buffer;
    vector<int> listwithnoowns;
    vector<node> tree, not_tree;
    node node_buffer;

    int conns, i, j, k, l, m, numcomps = -1, weight, sum,tempn;
    int startfrom = 0;
    bool finished_tree = false;
    bool has_owns = false;

    actual_owns_buffer.resize(2);

    //input data
    scanf("%d", &conns);
    for (k = 0; k < conns; k++){
        scanf("%d%d%d", &i, &j, &weight);

        //put into connection table
        if (i > numcomps || j > numcomps){
            numcomps = max(i, j);
            owns.resize(numcomps + 1);
            for (l = 0; l < numcomps + 1; l++){
                owns[l].resize(numcomps + 1);
                graph.resize(numcomps + 1);
            }
        }
        owns[i][j] = weight;

        //put in link list
        edge_buffer.from = i;
        edge_buffer.to = 0;
        edge_buffer.weight = weight;
        edge_buffer.visited = 0;
        graph[i].n = i;
        graph[j].n = j;
        graph[j].edges.push_back(edge_buffer);
        graph[i].edges.resize(graph[i].edges.size() + 1);
        graph[i].edges[graph[i].edges.size()-1].to = j;
        graph[i].edges[graph[i].edges.size() - 1].weight = weight;
        if (weight > 50){//search for obvious ownerships
            actual_owns_buffer[0] = i;
            actual_owns_buffer[1] = j;
            actual_owns.push_back(actual_owns_buffer);
        }
    }

    //if no obvs, exit
    if (actual_owns.size() == 0){
        exit(0);
    }

    for (m = 1; m <= numcomps; m++){//for each node in graph
        //make tree with node m as root
        finished_tree = false;
        tree.clear();
        for (j = 0; j < numcomps + 1; j++){ owns[j][0] = 0; }//acts like the "visited" flag
        node_buffer.n = m;
        node_buffer.used = false;
        tree.push_back(node_buffer);
        while (!finished_tree){
            finished_tree = true;
            for (i = 0; i < tree.size(); i++){//for each node in tree
                for (j = 1; j <= numcomps; j++){//for each company
                    if ((owns[tree[i].n][j]>50) && (owns[j][0] == 0)){//if found ownership
                        owns[j][0] = 1;
                        node_buffer.n = j;
                        tree.push_back(node_buffer);
                        finished_tree = false;
                        i = -1;
                        break;
                    }
                }
            }
        }

        if (tree.size() > 1){//a sum ownership is actually possible
            ////find nodes not in this tree and store them
            not_tree.clear();
            for (j = 1; j <= numcomps; j++){//for EVERY node
                if (not_in(tree, j)){
                    node_buffer.n = j;
                    not_tree.push_back(node_buffer);
                }
            }

            //calculate sums to each node not in tree from the nodes in the tree
        brake2:
            for (j = 0; j < not_tree.size(); j++){
                sum = 0;
                for (k = 0; k < graph[not_tree[j].n].edges.size(); k++){//for each edge leading to node not_tree[j]
                    for (l = 0; l < tree.size(); l++){//for all nodes in the tree
                        if (graph[not_tree[j].n].edges[k].from == tree[l].n){//if this edge source is in tree and not flagged(at start all "used" flags are set to true)
                            sum += graph[not_tree[j].n].edges[k].weight;
                        }
                        if (sum > 50){
                            node_buffer.n = not_tree[j].n;
                            tree.push_back(node_buffer);
                            not_tree.erase(not_tree.begin() + j);
                            goto brake2;
                        }
                    }
                }
            }
            
            //store the owns found
            actual_owns_buffer[0] = tree[0].n;
            for (i = 1; i < tree.size(); i++){
                actual_owns_buffer[1] = tree[i].n;
                actual_owns.push_back(actual_owns_buffer);
            }
        }
    }

    //clean up-remove duplicates and sames
    vector<vector<int> > final_ans;
    for (i = 0; i < actual_owns.size() - 1; i++){
        for (j = i + 1; j < actual_owns.size(); j++){
            if ((actual_owns[i][1] == actual_owns[j][1]) && (actual_owns[i][0] == actual_owns[j][0])){//if found duplicate [1]and duplicate[0]
                actual_owns[j][0] = -3123;
                actual_owns[j][1] = -1323;
            }
            if (actual_owns[j][1] == actual_owns[j][0]){//if same digit
                actual_owns[j][0] = -3123;
                actual_owns[j][1] = -1323;
            }
        }
    }

    for (i = 0; i < actual_owns.size(); i++){
        if (actual_owns[i][0] >= 0){
            final_ans.push_back(actual_owns[i]);
        }
    }

    //sort answer
    vector<int> temp;
    for (i = 0; i < final_ans.size() - 1; i++){
        for (j = i; j < final_ans.size(); j++){
            if (final_ans[i][0] * 1000 + final_ans[i][1]>final_ans[j][0] * 1000 + final_ans[j][1]){//just multiply first num by 1000 to skip lexicographical check
                temp = final_ans[i];
                final_ans[i] = final_ans[j];
                final_ans[j] = temp;
            }
        }
    }

    //output
    for (i = 0; i < final_ans.size(); i++){
        printf("%d %d\n", final_ans[i][0], final_ans[i][1]);
    }
}
