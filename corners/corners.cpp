//initial idea: solves hellenico corners problem by modified flood fill
//flood fill doesnt work
//out-of-the-box idea: BFS with memoization (the board is not the graph, the moves are 

//#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include <utility>
#include <set>
#include <queue>

#include <algorithm>

#define pawn 3
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

void makeNextPositionList(set<vector<pair<int, int> > >& nps, vector<vector<int> > board, vector<pair<int, int> > pawn_pos) {
	int i;
	pair<int, int> temp;
	//place pawns onto this board
	for (i = 0; i < 4; i++) {
		board[pawn_pos[i].first][pawn_pos[i].second] = pawn;
	}

	//check where pawn i can go and store the pawn_pos of that move
	for (i = 0; i < 4; i++) {
		pair<int, int> currentPos;
		currentPos = pawn_pos[i];
		//left 1?
		if ((currentPos.second >= 1) && (board[currentPos.first][currentPos.second - 1] == empty)) {
			temp = pawn_pos[i];
			pawn_pos[i] = make_pair(currentPos.first, currentPos.second - 1);
			nps.insert(pawn_pos);
			pawn_pos[i] = temp;
		}
		//left 2?
		if ((currentPos.second >= 2) && (board[currentPos.first][currentPos.second - 2] == empty) && (board[currentPos.first][currentPos.second - 1] != flag)) {
			temp = pawn_pos[i];
			pawn_pos[i] = make_pair(currentPos.first, currentPos.second - 2);
			nps.insert(pawn_pos);
			pawn_pos[i] = temp;
		}
		//right 1?
		if ((currentPos.second <= 4) && (board[currentPos.first][currentPos.second + 1] == empty)) {
			temp = pawn_pos[i];
			pawn_pos[i] = make_pair(currentPos.first, currentPos.second + 1);
			nps.insert(pawn_pos);
			pawn_pos[i] = temp;
		}
		//right 2?
		if ((currentPos.second <= 3) && (board[currentPos.first][currentPos.second + 2] == empty) && (board[currentPos.first][currentPos.second + 1] != flag)) {
			temp = pawn_pos[i];
			pawn_pos[i] = make_pair(currentPos.first, currentPos.second + 2);
			nps.insert(pawn_pos);
			pawn_pos[i] = temp;
		}
		//up 1?
		if ((currentPos.first >= 1) && (board[currentPos.first - 1][currentPos.second] == empty)) {
			temp = pawn_pos[i];
			pawn_pos[i] = make_pair(currentPos.first-1, currentPos.second);
			nps.insert(pawn_pos);
			pawn_pos[i] = temp;
		}
		//up 2?
		if ((currentPos.first >= 2) && (board[currentPos.first - 2][currentPos.second] == empty) && (board[currentPos.first - 1][currentPos.second] != flag)) {
			temp = pawn_pos[i];
			pawn_pos[i] = make_pair(currentPos.first-2, currentPos.second);
			nps.insert(pawn_pos);
			pawn_pos[i] = temp;
		}
		//down 1?
		if ((currentPos.first <= 4) && (board[currentPos.first + 1][currentPos.second] == empty)) {
			temp = pawn_pos[i];
			pawn_pos[i] = make_pair(currentPos.first+1, currentPos.second);
			nps.insert(pawn_pos);
			pawn_pos[i] = temp;
		}
		//down 2?
		if ((currentPos.first <= 3) && (board[currentPos.first + 2][currentPos.second] == empty) && (board[currentPos.first + 1][currentPos.second] != flag)) {
			temp = pawn_pos[i];
			pawn_pos[i] = make_pair(currentPos.first + 2, currentPos.second);
			nps.insert(pawn_pos);
			pawn_pos[i] = temp;
		}
	}
}

bool isDone(vector<pair<int,int> > pawn_pos) {
	vector<vector<int> > fakeboard;
	int i;
	fakeboard.resize(6);
	for (i = 0; i < 6; i++) {
		fakeboard[i].resize(6);
	}
	for (i = 0; i < 4; i++) {
		fakeboard[pawn_pos[i].first][pawn_pos[i].second] = pawn;
	}
	if ((fakeboard[0][0] == pawn) && (fakeboard[0][1] == pawn) && (fakeboard[1][0] == pawn) && (fakeboard[1][1] == pawn)) {
		return true;
	}
	return false;
}

int bfs(vector<vector<int> > board,int step_no,vector<pair<int,int> > pawn_pos) {
	int i;
	vector<vector<pair<int, int> > > n;
	int step;
	set<vector<pair<int, int> > > next_positions_set,nextnext_positions_set;
	makeNextPositionList(next_positions_set,board,pawn_pos);
	step_no++;

	//while(not done){}
	while (true) {
		set<vector<pair<int, int> > >::iterator it;
		//for each next position in next_positions
		for (it = next_positions_set.begin(); it != next_positions_set.end(); ++it) {
			if (isDone(*it)) {
				return step_no;
				break;
			}
			makeNextPositionList(nextnext_positions_set, board, *it);
		}
		step_no++;
		cout << step_no << endl;
		next_positions_set.clear();
		next_positions_set.swap(nextnext_positions_set);
	}
	return step_no;
}
int main() {
	ifstream inf("corners.in");
	ofstream ouf("corners.out");
	char x;
	int i, j;

	vector<vector<int> > board;
	board.resize(6);
	for (i = 0; i < 6; i++) {
		board[i].resize(6);
	}
	//read the board from stdin
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 6; j++) {
			inf >> x;
			switch (x) {
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
	board[5][5] = pawn;
	board[4][5] = pawn;
	board[4][4] = pawn;
	board[5][4] = pawn;
	vector<pair<int,int> > pawn_pos;
	pawn_pos.resize(4);
	pawn_pos[0] = make_pair(5, 5);
	pawn_pos[1] = make_pair(4, 5);
	pawn_pos[2] = make_pair(4, 4);
	pawn_pos[3] = make_pair(5, 4);

	ouf << bfs(board, 0, pawn_pos) << endl;
	return 0;
}
