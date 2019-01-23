//initial idea: solves hellenico corners problem by modified flood fill
//flood fill doesnt work
//out-of-the-box idea: BFS with memoization (the board is not the graph, the moves are 

//#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include <utility>
#include <queue>
#include <algorithm>

#define flag 2
#define rock 1
#define empty 0

using namespace std;

typedef struct node {
	int i, j, dist;
	node* prev_node;
}node;

node nodeConstr(int i, int j, int dist, node* prev_node) {
	node temp;
	temp.i = i;
	temp.j = j;
	temp.dist = dist;
	temp.prev_node = prev_node;
	return temp;
}

vector<node> getNextPositions(vector<vector<int> > &board, node currentPos,int dist) {
	vector<node> nextPositions;
	node tempN;
	//left 1?
	if ((currentPos.j >= 1) && (board[currentPos.i][currentPos.j - 1] == empty)) {
		nextPositions.push_back(nodeConstr(currentPos.i, currentPos.j - 1, dist + 1,&currentPos));
	}
	//left 2?
	if ((currentPos.j >= 2) && (board[currentPos.i][currentPos.j - 2] == empty) && (board[currentPos.i][currentPos.j - 1] != flag)){
		nextPositions.push_back(nodeConstr(currentPos.i, currentPos.j - 2, dist + 1, &currentPos));
	}
	//right 1?
	if ((currentPos.j <= 4) && (board[currentPos.i][currentPos.j + 1] == empty)) {
		nextPositions.push_back(nodeConstr(currentPos.i, currentPos.j + 1, dist + 1, &currentPos));
	}
	//right 2?
	if ((currentPos.j <= 3) && (board[currentPos.i][currentPos.j + 2] == empty) && (board[currentPos.i][currentPos.j + 1] != flag)) {
		nextPositions.push_back(nodeConstr(currentPos.i, currentPos.j + 2, dist + 1, &currentPos));
	}
	//up 1?
	if ((currentPos.i >= 1) && (board[currentPos.i - 1][currentPos.j] == empty)) {
		nextPositions.push_back(nodeConstr(currentPos.i - 1, currentPos.j, dist + 1, &currentPos));
	}
	//up 2?
	if ((currentPos.i >= 2) && (board[currentPos.i - 2][currentPos.j] == empty) && (board[currentPos.i - 1][currentPos.j] != flag)) {
		nextPositions.push_back(nodeConstr(currentPos.i - 2, currentPos.j, dist + 1, &currentPos));
	}
	//down 1?
	if ((currentPos.i <= 4) && (board[currentPos.i + 1][currentPos.j] == empty)) {
		nextPositions.push_back(nodeConstr(currentPos.i + 1, currentPos.j, dist + 1, &currentPos));
	}
	//down 2?
	if ((currentPos.i <= 3) && (board[currentPos.i + 2][currentPos.j] == empty) && (board[currentPos.i + 1][currentPos.j] != flag)) {
		nextPositions.push_back(nodeConstr(currentPos.i + 2, currentPos.j, dist + 1, &currentPos));
	}
}

void dfs(node current_node) {
	//exit case
	if (current_node.i == 0 && current_node.j == 0) {
		return;
	}

}
int main() {
    ifstream inf("corners.in");
    ofstream ouf("corners.out");
    char x;
	int i, j;

    vector<vector<int> > board;
    board.resize(6);
    for(i = 0; i < 6; i++) {
        board[i].resize(6);
    }
    //read the board from stdin
    for(i = 0; i < 6; i++) {
        for(j = 0; j < 6; j++) {
            inf >> x;
            switch(x) {
            case '.':
                board[i][j] = empty;
                break;
            case 'r':
                board[i][j] = flag;
                break;
            case 's':
                board[i][j] = rock;
                break;
            default:
                exit(1337);
            }
        }
    }

	//cout << sum << endl;
    //ouf<<sum<<endl;
    return 0;
}
