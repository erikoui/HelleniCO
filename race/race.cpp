#include <stdio.h>  
#include <stdlib.h>  
#include <vector>  
#include <algorithm>  
#include <stack>  
#include <list>  
using namespace std;  

vector<vector<int> > paths;  
vector<int> cur_path;  
vector<int> visited;
bool grv;//grv=global return value

typedef struct{  
	int distance,parent;  
}node;  


bool leads_to_end(vector<vector<int> > race,int node_to_check,int current_node,int last){
	int i,j;
	bool ret=false;
	if(current_node==last){//reached the last node
		return true; 
	}else if(current_node==node_to_check){
		return false;
	}else{  
		for(i=0;i<race[current_node].size();i++){//for each node connected to current node  
			int t=visited.size()-1;  
			for(j=0;j<t;j++){//chenck if i already visited the next node  
				if(race[current_node][i]==visited[j]){  
					j=-50;  
					break;  
				}  
			}  
			if(j!=-50){  
				visited.push_back(race[current_node][i]);  
				return leads_to_end(race,node_to_check,race[current_node][i],last);  
			}  
		}  
	}  
}

void leadsTo0(int node,int check,int current_node,vector<vector<int> > race,vector<bool> visiteed){//checks if you can get from 0 to node without passing through check
	//node=our goal node(the one we try to go to without going through the one before it)
	if(visiteed[current_node]){
		return;
	}
	if(current_node==check){//passing through node currently being checked if is inevitable
		return;
	}
	if(current_node==node){//reached goal node(without passing through node currently being checked if is inevitable)
		grv=true;
		return;
	}else if(current_node==check){//passing through node currently being checked if is inevitable
		return;
	}else{
		int i;
		for(i=0;(i<race[current_node].size())&&(!grv);i++){
			visiteed[current_node]=true;
			leadsTo0(node,check,race[current_node][i],race,visiteed);
		}
	}
}


int main(){  
	vector<bool> v;//visiteed
	freopen("race.in","r",stdin);  
	int buff,i=0,j,k;  
	int num_of_nodes;  
	int maxd=-1;//max distance from node 0  
	vector<int> inevitable_nodes;  
	vector<int> breakp;  
	vector<int> buffer;//read line from file  
	vector<int> queue;//for bfs  
	vector<node> node_distance;//node_distance[i].distance=distance;  
	vector<vector<int> > race;//adjacency list  
	vector<vector<int> > depth_adjusted_race;  
	v.resize(101);
	//read file into race vector  
	scanf("%d",&buff);  
	while(buff!=-1){  
		while(buff!=-2){  
			buffer.push_back(buff);  
			scanf("%d",&buff);  
		}  
		race.push_back(buffer);  
		buffer.clear();  
		i++;  
		scanf("%d",&buff);  
	}  
	num_of_nodes=i;//total number of nodes  

	//BFS to make nods_distance
	node_distance.resize(num_of_nodes);  
	for(i=0;i<num_of_nodes;i++){  
		node_distance[i].distance=9999;  
	}  

	node_distance[0].distance=0;  
	queue.push_back(0);  
	while(queue.size()!=0){  
		int curr=queue[0];  
		queue.erase(queue.begin());  
		for(i=0;i<race[curr].size();i++){  
			if(node_distance[race[curr][i]].distance==9999){  
				node_distance[race[curr][i]].distance=node_distance[curr].distance+1;  
				node_distance[race[curr][i]].parent=curr;  
				queue.push_back(race[curr][i]);  
				if(node_distance[curr].distance+1>maxd){  
					maxd=node_distance[curr].distance+1;  
				}  
			}  
		}  
	}

	int cur_n=num_of_nodes-1;
	vector<int> sp;
	bool flag=false;
	sp.push_back(cur_n);
	while(cur_n!=0){
		sp.insert(sp.begin(),node_distance[cur_n].parent);
		cur_n=node_distance[cur_n].parent;
	}

	for(i=0;i<sp.size();i++){//for each node in shortest path
		v.clear();
		v.resize(101);
		flag=false;//asume sp[i] is inevitable
		for(j=i+1;j<sp.size();j++){//for each node after sp[i] in shortest path
			grv=false;
			leadsTo0(sp[j],sp[i],0,race,v);//check if 0 leads to sp[j] without passing through sp[i]
			if(grv){//i went to sp[j] without passing through sp[i] therefore sp[i] is not inevitable
				flag=true;
			}
		}
		if(!flag){//could not go to sp[i] withut passing through sp[j]
			inevitable_nodes.push_back(sp[i]);
		}
	}


	if(inevitable_nodes.size()!=0){
		if(inevitable_nodes[0]==0){
			inevitable_nodes.erase(inevitable_nodes.begin());
		}
		if(inevitable_nodes[inevitable_nodes.size()-1]==num_of_nodes-1){
			inevitable_nodes.pop_back();
		}
	}

	visited.clear();
	visited.resize(101);
	bool is_breakp=true;  
	int dist_of_cur_node=0;  
	int in_counter;//inevitable nodes vector counter
	int race_counter;
	int race_counter2;
	int connection;
	bool contains_0;
	for(in_counter=0;in_counter<inevitable_nodes.size();in_counter++){//for all inevitable nodes  
		dist_of_cur_node=node_distance[inevitable_nodes[in_counter]].distance;  
		//check if parents lead to inevitable_node[in_cpounter]
		vector<node>  ss;//subset that contains only nodes connected to inevitable_nodes[in_counter]


		//bfs to discover ss
		ss.resize(num_of_nodes);  
		queue.clear();
		for(i=0;i<num_of_nodes;i++){  
			ss[i].distance=9999;  
		}  
		contains_0=false;
		ss[inevitable_nodes[in_counter]].distance=0;  
		queue.push_back(inevitable_nodes[in_counter]);  
		while(queue.size()!=0){  
			int curr=queue[0];  
			queue.erase(queue.begin());  
			for(i=0;i<race[curr].size();i++){  
				if(ss[race[curr][i]].distance==9999){  
					ss[race[curr][i]].distance=ss[curr].distance+1;  
					ss[race[curr][i]].parent=curr;  
					if(race[curr][i]==0){
						contains_0=true;
					}
					queue.push_back(race[curr][i]);  
				}  
			}  
		}

		if(contains_0){
			is_breakp=false;
		}else{
			//check if any node in ss leads to any node before inevitable[in_count]
			for(i=0;i<ss.size();i++){
				if(ss[i].distance!=9999){
					grv=false;
					v.clear();
					v.resize(101);
					leadsTo0(i,inevitable_nodes[in_counter],0,race,v);
					if(grv){
						is_breakp=false;
					}
				}
			}
		}
		if(is_breakp){  
			breakp.push_back(inevitable_nodes[in_counter]);  
		}  
		is_breakp=true; 
	}




	//	for(race_counter=0;race_counter<race.size();race_counter++){//for all nodes in race
	//		if(dist_of_cur_node<node_distance[race_counter].distance){//current node(inevitable_nodes[in_counter]) is shallower than race[race counter]
	//			for(connection=0;connection<race[race_counter].size();connection++){//for each node connected to race[race_counter](which has a distance higher than inevitable_nodes[in_counter])
	//				if(node_distance[race[race_counter][connection]].distance<=dist_of_cur_node){//distance of node connected to the one after my inevitable node is less than distance of my inevitable node?
	//					//check if parents lead to inevitable_node[in_cpounter]
	//					vector<node>  ss;//subset that contains only nodes connected to inevitable_nodes[in_counter]
	//					
	//					
	//					//bfs to discover ss
	//					ss.resize(num_of_nodes);  
	//					queue.clear();
	//					for(i=0;i<num_of_nodes;i++){  
	//						ss[i].distance=9999;  
	//					}  
	//					contains_0=false;
	//					ss[inevitable_nodes[in_counter]].distance=0;  
	//					queue.push_back(inevitable_nodes[in_counter]);  
	//					while(queue.size()!=0){  
	//						int curr=queue[0];  
	//						queue.erase(queue.begin());  
	//						for(i=0;i<race[curr].size();i++){  
	//							if(ss[race[curr][i]].distance==9999){  
	//								ss[race[curr][i]].distance=ss[curr].distance+1;  
	//								ss[race[curr][i]].parent=curr;  
	//								if(race[curr][i]==0){
	//									contains_0=true;
	//								}
	//								queue.push_back(race[curr][i]);  
	//							}  
	//						}  
	//					}

	//					if(contains_0){
	//						is_breakp=false;
	//					}
	//					int p=ss[race[race_counter][connection]].parent;
	//					int ddd=node_distance[race[race_counter][connection]].distance;
	//					while(p!=0){
	//						if(ddd<=node_distance[inevitable_nodes[in_counter]].distance){
	//							is_breakp=false; 
	//							break;
	//						}
	//						p=ss[/*ss[race[race_counter][connection]].parent*/p].parent;
	//					}
	//				}  
	//			}  
	//		}  
	//	}  
	//	if(is_breakp){  
	//		breakp.push_back(inevitable_nodes[in_counter]);  
	//	}  
	//	is_breakp=true;  
	//}  

	if(breakp.size()!=0){
		if(breakp[0]==0){
			breakp.erase(breakp.begin());
		}
		if(breakp[breakp.size()-1]==num_of_nodes-1){
			breakp.pop_back();
		}
	}

	freopen("race.out","w",stdout);  
	sort(inevitable_nodes.begin(),inevitable_nodes.end());    
	printf("%d",inevitable_nodes.size());  
	for(i=0;i<inevitable_nodes.size();i++){  
		printf(" %d",inevitable_nodes[i]);  
	}  
	sort(breakp.begin(),breakp.end());    
	printf("\n%d",breakp.size());  
	for(i=0;i<breakp.size();i++){  
		printf(" %d",breakp[i]);  
	}  


	return 0;  
}  
