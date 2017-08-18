#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
vector<vector<int> > visited;
int sum;

typedef struct trip{
	int i,j;
	char ne;
}trip;

void dfs(vector<vector<unsigned int> > &castl,int n,int m,int i,int j,int c){
	bool f=false;
	visited[i][j]=c;
	if(castl[i][j]%2==0){//no wall on left
		if(!visited[i][j-1]){
			++sum;
			dfs(castl,n,m,i,j-1,c);
		}
	}
	if((castl[i][j]>>1)%2==0){//no wall on up
		if(!visited[i-1][j]){
			++sum;
			dfs(castl,n,m,i-1,j,c);
		}
	}
	if((castl[i][j]>>2)%2==0){//no wall on right
		if(!visited[i][j+1]){
			++sum;
			dfs(castl,n,m,i,j+1,c);
		}
	}
	if((castl[i][j]>>3)%2==0){//no wall on down
		if(!visited[i+1][j]){
			++sum;
			dfs(castl,n,m,i+1,j,c);
		}
	}
}

int max(vector<int> &a){
	int i;
	int max=a[0];
	for(i=1;i<a.size();i++){
		if(a[i]>max){
			max=a[i];
		}
	}
	return max;
}

int max(vector<int> &a,vector<int> &b,vector<int> &sum){
	int i;
	int max=sum[a[0]-1]+sum[b[0]-1];
	for(i=1;i<a.size();i++){
		if(sum[a[i]-1]+sum[b[i]-1]>max){
			max=sum[a[i]-1]+sum[b[i]-1];
		}
	}
	return max;
}

bool notcombointbl(vector<int> &start,vector<int> &end,int a/*visited[i][j]*/,int b/*visited[i][j+1]*/){
	int i;
	for(i=0;i<start.size();i++){
		if((a==start[i])||(b==start[i])){
			if((b==end[i])||(a==end[i])){
				return false;
			}
		}
	}
	return true;
}

void fixstart(vector<int> &start,vector<int> &finish){
	int i;
	for(i=0;i<start.size();i++){
		if(finish[i]>start[i]){
			swap(start[i],finish[i]);
		}
	}
}

bool sortby(const trip &a,const trip &b){
	if(a.j!=b.j)
		return a.j<b.j;
	if(a.i!=b.i)
		return a.i>b.i;
	return a.ne>=b.ne;
}

int main(){
	freopen("castle.in","r",stdin);
	freopen("castle.out","w",stdout);

	vector<vector<unsigned int> > castle;
	vector<int>s;
	vector<int> start;
	vector<int> finish;
	int i,j,n,m,x=1;
	trip walls[1000];
	int numw=0;
	int maxx;
	int conn[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int cc=0;

	cin>>n>>m;

	castle.resize(n);
	visited.resize(n);
	for(i=0;i<n;i++){
		castle[i].resize(m);
		visited[i].resize(m);
	}


	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			cin>>castle[i][j];
			visited[i][j]=false;
		}
	}

	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(!visited[i][j]){
				dfs(castle,n,m,i,j,x);
				++x;
			}
		}
	}
	s.resize(x);
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			s[visited[i][j]]++;
		}
	}
	cout<<x-1<<endl<<max(s)<<endl;//num of rooms & biggest room

	//analyse visited table(make connection graph)(find neighboring rooms)
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(j<m-1){
				if(visited[i][j+1]!=visited[i][j]){
					if(notcombointbl(start,finish,visited[i][j+1],visited[i][j])){
						start.push_back(min(visited[i][j+1],visited[i][j]));
						finish.push_back(max(visited[i][j+1],visited[i][j]));
					}
				}
			}if(i<n-1){
				if(visited[i+1][j]!=visited[i][j]){
					if(notcombointbl(start,finish,visited[i+1][j],visited[i][j])){
						start.push_back(min(visited[i+1][j],visited[i][j]));
						finish.push_back(max(visited[i+1][j],visited[i][j]));
					}
				}
			}
		}
	}

	//find biggest room
	maxx=s[start[0]]+s[finish[0]];
	for(i=0;i<start.size();i++){
		if(s[start[i]]+s[finish[i]]>maxx){
			maxx=s[start[i]]+s[finish[i]];
		}
	}
	cout<<maxx<<endl;

	for(i=0;i<start.size();i++){
		if(s[start[i]]+s[finish[i]]==maxx){
			conn[cc]=i;
			cc++;
		}
	}



	//find the door
	for(int l=0;l<cc;l++){
		for(j=0;j<m-1;j++){
			for(i=n-1;i>=0;i--){
				if(visited[i][j]==start[conn[l]]){
					if(visited[i][j+1]==finish[conn[l]]){
						walls[numw].i=i;
						walls[numw].j=j;
						walls[numw].ne='E';
						numw++;
					}
				}else if(visited[i][j+1]==start[conn[l]]){
					if(visited[i][j]==finish[conn[l]]){
						walls[numw].i=i;
						walls[numw].j=j;
						walls[numw].ne='E';
						numw++;
					}
				}
			}
		}
	}

	for(int l=0;l<cc;l++){
		for(j=0;j<m;j++){
			for(i=n-1;i>=1;i--){
				if(visited[i][j]==start[conn[l]]){
					if(visited[i-1][j]==finish[conn[l]]){
						walls[numw].i=i;
						walls[numw].j=j;
						walls[numw].ne='N';
						numw++;
					}
				}
				else if(visited[i-1][j]==start[conn[l]]){
					if(visited[i][j]==finish[conn[l]]){
						walls[numw].i=i;
						walls[numw].j=j;
						walls[numw].ne='N';
						numw++;
					}
				}
			}
		}
	}


	sort(walls,walls+numw,sortby);
	cout<<walls[0].i+1<<" "<<walls[0].j+1<<" "<<walls[0].ne<<endl;
	return 0;
}
