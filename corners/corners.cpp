//gets 7/10

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#define flag 2
#define rock 1
#define empty 0

using namespace std;

typedef struct{
    int i, j;
}coord;

void flood(coord p, coord f, vector<vector<int> >& b, vector<vector<vector<int> > >& d, int l){//position(to/current),from,board,distances,level
    //check oob

    if (p.i > 5){
        return;
    }
    if (p.j > 5){
        return;
    }
    if (p.i < 0){
        return;
    }
    if (p.j < 0){
        return;
    }

    if ((p.i == f.i + 2) && (b[f.i + 1][f.j] == flag))
        return;
    if ((p.i == f.i - 2) && (b[f.i - 1][f.j] == flag))
        return;
    if ((p.j == f.j + 2) && (b[f.i][f.j + 1] == flag))
        return;
    if ((p.j == f.j - 2) && (b[f.i][f.j - 1] == flag))
        return;
    //current cell is where im goin, neds to be empty
    if (b[p.i][p.j] != 0){
        return;
    }

    //  ouf << f.i << "," << f.j << "(" << d[f.i][f.j][l] << ") -> " << p.i << ", " << p.j << "(" << d[p.i][p.j][l]<<endl;
    if ((d[f.i][f.j][l] + 1) < d[p.i][p.j][l]){
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

void flooda(coord p, coord f, vector<vector<int> >& b, vector<vector<vector<int> > >& d, int l){//position(to/current),from,board,distances,level
    //check oob

    if (p.i > 5){
        return;
    }
    if (p.j > 5){
        return;
    }
    if (p.i < 0){
        return;
    }
    if (p.j < 0){
        return;
    }
    if ((p.i == f.i + 2) && (b[f.i + 1][f.j] == flag))
        return;
    if ((p.i == f.i - 2) && (b[f.i - 1][f.j] == flag))
        return;
    if ((p.j == f.j + 2) && (b[f.i][f.j + 1] == flag))
        return;
    if ((p.j == f.j - 2) && (b[f.i][f.j - 1] == flag))
        return;

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

int main() {
    ifstream inf("corners.in");
    ofstream ouf("corners.out");
    int i, j, k, l;
    int initval = 200;
    char x;
    int times;

    vector<vector<int> > board;

    vector<vector<vector<int> > > dist;
    dist.resize(6);
    board.resize(6);
    for (i = 0; i < 6; i++){
        dist[i].resize(6);
        board[i].resize(6);
        for (j = 0; j < 6; j++){
            dist[i][j].resize(4);
        }
    }
    //read the board from stdin    
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            inf >> x;
            dist[i][j][1] = initval;
            dist[i][j][2] = initval;
            dist[i][j][3] = initval;
            dist[i][j][0] = initval;
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
    dist[5][5][0] = 0;//init L1
    dist[5][4][1] = 0;
    dist[4][5][2] = 0;
    dist[4][4][3] = 0;
    
    coord start,to;
    start.i = 5;
    start.j = 5;
    to.i = 5;
    to.j = 4;
    flooda(start, start, board, dist, 0);

    start.i = 5;
    start.j = 4;
    to.i = 5;
    to.j = 3;
    flooda(start, start, board, dist, 1);

    start.i = 4;
    start.j = 5;
    to.i = 4;
    to.j = 4;
    flooda(start, start, board, dist, 2);

    start.i = 4;
    start.j = 4;
    to.i = 4;
    to.j = 3;
    flooda(start, start, board, dist, 3);
    
    vector<int> order;
    order.push_back(0);
    order.push_back(1);
    order.push_back(2);
    order.push_back(3);

    int minsum = 5000;
    int sum = 0;
    coord c[4];
    for (i = 0; i < 24; i++){
        sum = 0;
        sum += dist[0][0][order[0]]-1;
        sum += dist[1][0][order[1]]-1;
        sum += dist[0][1][order[2]]-1;
        sum += dist[1][1][order[3]]-1;
        if (sum < minsum){
            minsum = sum;
        }
        next_permutation(order.begin(), order.end());
    }
    if (minsum > 199){
        minsum = -1;
    }
    ouf << minsum << endl;
    return 0;
}
