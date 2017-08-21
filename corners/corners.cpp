//solves hellenico corners problem by modified flood fill
//floods for each poul cyclically instead of assuming that 2 moves are always possible

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>

#define flag 2
#define rock 1
#define empty 0

using namespace std;

typedef struct {
    int i, j;
} coord;

void flood(coord p, coord f, vector<vector<int> >& b, vector<vector<vector<int> > >& d, int l) { //position(to/current),from,board,distances,level
    //check oob

    if(p.i > 5) {
        return;
    }
    if(p.j > 5) {
        return;
    }
    if(p.i < 0) {
        return;
    }
    if(p.j < 0) {
        return;
    }

    if((p.i == f.i + 2) && (b[f.i + 1][f.j] == flag))
        return;
    if((p.i == f.i - 2) && (b[f.i - 1][f.j] == flag))
        return;
    if((p.j == f.j + 2) && (b[f.i][f.j + 1] == flag))
        return;
    if((p.j == f.j - 2) && (b[f.i][f.j - 1] == flag))
        return;
    //current cell is where im goin, neds to be empty
    if(b[p.i][p.j] != 0) {
        return;
    }

    //  ouf << f.i << "," << f.j << "(" << d[f.i][f.j][l] << ") -> " << p.i << ", " << p.j << "(" << d[p.i][p.j][l]<<endl;
    if((d[f.i][f.j][l] + 1) < d[p.i][p.j][l]) {
        d[p.i][p.j][l] = d[f.i][f.j][l] + 1;


        coord n;//next
        n.j = p.j;
        n.i = p.i + 1;
        flood(n, p, b, d, l);
        n.i = p.i + 2;
        flood(n, p, b, d, l);
        n.i = p.i - 1;
        flood(n, p, b, d, l);
        n.i = p.i - 2;
        flood(n, p, b, d, l);
        n.i = p.i;
        n.j = p.j + 1;
        flood(n, p, b, d, l);
        n.j = p.j + 2;
        flood(n, p, b, d, l);
        n.j = p.j - 1;
        flood(n, p, b, d, l);
        n.j = p.j - 2;
        flood(n, p, b, d, l);
    }

}

bool setav(vector<vector<vector<int> > >& d, int i, int j, int level, int amount) {
    //checks if its ok to set a new dist to d[i][j][level] and does so

    if(i > 5) {
        return false;
    }
    if(j > 5) {
        return false;
    }
    if(i < 0) {
        return false;
    }
    if(j < 0) {
        return false;
    }
    if(d[i][j][level] > amount) {
        d[i][j][level] = amount;
        return true;
    }
    return false;
}

void floodFill(vector<vector<int> >& b, vector<vector<vector<int> > >& d, vector<vector<bool> > visited, int i, int j, int l) { //position(to/current),from,board,distances,level
    //check oob
    if(i > 5) {
        return;
    }
    if(j > 5) {
        return;
    }
    if(i < 0) {
        return;
    }
    if(j < 0) {
        return;
    }

    queue<coord> Q;
    coord tc;
    if(i > 0) {
        if(b[i - 1][j] == empty) { //up1
            if(setav(d, i - 1, j, l, d[i][j][l] + 1)) {
                visited[i - 1][j] = true;
                tc.i = i - 1;
                tc.j = j;
                Q.push(tc);
            }
        }
    }

    if(i > 1) {
        if((b[i - 2][j] == empty) && ((b[i - 1][j] == rock) || (visited[i][j]))) { //up2
            if(setav(d, i - 2, j, l, d[i][j][l] + 1)) {
                visited[i - 2][j] = true;
                tc.i = i - 2;
                tc.j = j;
                Q.push(tc);
            }
        }
    }

    if(i < 5) {
        if(b[i + 1][j] == empty) { //down1
            if(setav(d, i + 1, j, l, d[i][j][l] + 1)) {
                visited[i + 1][j] = true;
                tc.i = i + 1;
                tc.j = j;
                Q.push(tc);
            }
        }
    }

    if(i < 4) {
        if((b[i + 2][j] == empty) && ((b[i + 1][j] == rock) || (visited[i][j]))) { //down2
            if(setav(d, i + 2, j, l, d[i][j][l] + 1)) {
                visited[i + 2][j] = true;
                tc.i = i + 2;
                tc.j = j;
                Q.push(tc);
            }
        }
    }

    if(j > 0) {
        if(b[i][j - 1] == empty) { //left1
            if(setav(d, i, j - 1, l, d[i][j][l] + 1)) {
                visited[i][j - 1] = true;
                tc.i = i;
                tc.j = j - 1;
                Q.push(tc);
            }
        }
    }

    if(j > 1) {
        if((b[i][j - 2] == empty) && ((b[i][j - 2] == rock) || (visited[i][j]))) { //left2
            if(setav(d, i, j - 2, l, d[i][j][l] + 1)) {
                visited[i][j - 2] = true;
                tc.i = i;
                tc.j = j - 2;
                Q.push(tc);
            }
        }
    }

    if(j < 5) {
        if(b[i][j + 1] == empty) { //right1
            if(setav(d, i, j + 1, l, d[i][j][l] + 1)) {
                visited[i][j + 1] = true;
                tc.i = i;
                tc.j = j + 1;
                Q.push(tc);
            }
        }
    }
    
    if(j < 4) {
        if((b[i][j + 2] == empty) && ((b[i][j + 2] == rock) || (visited[i][j]))) { //right2
            if(setav(d, i, j + 2, l, d[i][j][l] + 1)) {
                visited[i][j + 2] = true;
                tc.i = i;
                tc.j = j + 2;
                Q.push(tc);
            }
        }
    }
    int x, y, lev;
    if(Q.size()!=0){
    for(x = 0; x < 6; x++) {
        for(y = 0; y < 6; y++) {
            for(lev = 0; lev < 4; lev++) {
                if(d[x][y][(l + 1) % 4] != 1337) {
                    floodFill(b, d, visited, x, y, (l + 1) % 4);
                }
            }
        }
    }
    
    }
}

int main() {
    ifstream inf("corners.in");
    ofstream ouf("corners.out");
    int i, j, k, l;
    int initval = 1337;
    char x;
    int times;

    vector<vector<int> > board;
    vector<vector<bool> > visited;
    vector<vector<vector<int> > > dist;
    dist.resize(6);
    board.resize(6);
    visited.resize(6);
    for(i = 0; i < 6; i++) {
        dist[i].resize(6);
        visited[i].resize(6);
        board[i].resize(6);
        for(j = 0; j < 6; j++) {
            dist[i][j].resize(4);
        }
    }
    //read the board from stdin
    for(i = 0; i < 6; i++) {
        for(j = 0; j < 6; j++) {
            inf >> x;
            dist[i][j][1] = initval;
            dist[i][j][2] = initval;
            dist[i][j][3] = initval;
            dist[i][j][0] = initval;
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

    dist[5][5][0] = 0;//init L1
    dist[5][4][1] = 0;
    dist[4][5][2] = 0;
    dist[4][4][3] = 0;
    visited[5][5] = true;
    visited[5][4] = true;
    visited[4][5] = true;
    visited[4][4] = true;

    floodFill(board, dist, visited, 4, 4, 3);


    vector<int> order;
    order.push_back(0);
    order.push_back(1);
    order.push_back(2);
    order.push_back(3);

    int minsum = 5000;
    int sum = 0;
    coord c[4];
    for(i = 0; i < 24; i++) {
        sum = 0;
        sum += dist[0][0][order[0]] - 1;
        sum += dist[1][0][order[1]] - 1;
        sum += dist[0][1][order[2]] - 1;
        sum += dist[1][1][order[3]] - 1;
        if(sum < minsum) {
            minsum = sum;
        }
        next_permutation(order.begin(), order.end());
    }
    if(minsum > 199) {
        minsum = -1;
    }
    ouf << minsum << endl;
    return 0;
}
