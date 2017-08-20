//solves hellenico corners problem by brute force.
//hopefully will need max 2^20 iterations
//uses a 2d vector containing the possible moves from each position
//when something moves it changes the possible moves around it because things can jump over it now

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#define flag 2
#define rock 1
#define empty 0

#define up1 0
#define up2 1
#define down1 2
#define down2 3
#define left1 4
#define left2 5
#define right1 6
#define right2 7

using namespace std;

typedef struct {        
    int i, j;
} coord;

struct square {
    bool cangoto[8];
};

//TODO: function that prints the board (e.g. TTFFTF)
//                                           TTFTFT
//                                           FTTTTT
//                                            ....

//TODO: DFS brute force
int mind;

bool cmpCoord(coord c,coord d){
    if(c.i<d.i){
        return true;
    }
    if(c.i==d.i){
        if(c.j<d.j){
            return true;
        }
    }
    return false;
}

bool operator==(const coord& a, const coord& b){
    return (a.i==b.i)&&(a.j==b.j);
}

bool done(vector<coord> poulpos){
    sort(poulpos.begin(),poulpos.end(),cmpCoord);
    coord zz,zo,oz,oo;
    
    zz.i=0;
    zz.j=0;
    
    zo.i=0;
    zo.j=1;
    
    oz.i=1;
    oz.j=0;
    
    oo.i=1;
    oo.j=1;
    
    if((poulpos[0]==zz)&&(poulpos[1]==zo)&&(poulpos[2]==oz)&&(poulpos[3]==oo)){
        return true;
    }else{
        return false;
    }
}

void dfs(vector<vector<square> > b, vector<coord> poulpos, int dist,vector<vector<bool> > visited) {
    if(done(poulpos)) {
        if(dist < mind) {
            mind = dist;
        }
    }
    int j;
    //TODO: mark nodes which im going to as visited
    for(j = 0; j < 4; j++) { //each poul
        if(b[poulpos[j].i][poulpos[j].j].cangoto[up1]) { //if current poul can go to direction
            //move it to direction
            poulpos[j].i-=1;
            dfs(b,poulpos,dist+1,visited);
            poulpos[j].i+=1;
        }
        if(b[poulpos[j].i][poulpos[j].j].cangoto[up2]) { //if current poul can go to direction
            //move it to direction
            poulpos[j].i-=2;
            dfs(b,poulpos,dist+1,visited);
            poulpos[j].i+=2;
        }
        if(b[poulpos[j].i][poulpos[j].j].cangoto[down1]) { //if current poul can go to direction
            //move it to direction
            poulpos[j].i+=1;
            dfs(b,poulpos,dist+1,visited);
            poulpos[j].i-=1;
        }
        if(b[poulpos[j].i][poulpos[j].j].cangoto[down2]) { //if current poul can go to direction
            //move it to direction
            poulpos[j].i+=2;
            dfs(b,poulpos,dist+1,visited);
            poulpos[j].i-=2;
        }
        if(b[poulpos[j].i][poulpos[j].j].cangoto[left1]) { //if current poul can go to direction
            //move it to direction
            poulpos[j].j-=1;
            dfs(b,poulpos,dist+1,visited);
            poulpos[j].j+=1;
        }
        if(b[poulpos[j].i][poulpos[j].j].cangoto[left2]) { //if current poul can go to direction
            //move it to direction
            poulpos[j].j-=2;
            dfs(b,poulpos,dist+1,visited);
            poulpos[j].j+=2;
        }
        if(b[poulpos[j].i][poulpos[j].j].cangoto[right1]) { //if current poul can go to direction
            //move it to direction
            poulpos[j].j+=1;
            dfs(b,poulpos,dist+1,visited);
            poulpos[j].j-=1;
        }
        if(b[poulpos[j].i][poulpos[j].j].cangoto[right2]) { //if current poul can go to direction
            //move it to direction
            poulpos[j].j+=2;
            dfs(b,poulpos,dist+1,visited);
            poulpos[j].j-=2;
        }
    }
}

void readBoard(ifstream& inf, vector<vector<square> >& board) {
    int i, j, k;
    char x;
    //read the board from stdin
    //+ is right/down
    for(i = 0; i < 6; i++) {
        for(j = 0; j < 6; j++) {
            for(k = 0; k < 8; k++) {
                board[i][j].cangoto[k] = true;
            }
        }
    }

    for(i = 0; i < 6; i++) {
        for(j = 0; j < 6; j++) {
            inf >> x;
            if(x == 's') { //stone
                if(j < 5) {
                    board[i][j + 1].cangoto[left1] = false;
                    board[i][j + 1].cangoto[left2] = true;
                    if(j < 4) {
                        board[i][j + 2].cangoto[left2] = false;
                    }
                }
                if(j > 0) {
                    board[i][j - 1].cangoto[right1] = false;
                    board[i][j - 1].cangoto[right2] = true;
                    if(j > 1) {
                        board[i][j - 2].cangoto[right2] = false;
                    }
                }

                if(i < 5) {
                    board[i + 1][j].cangoto[up1] = false;
                    board[i + 1][j].cangoto[up2] = true;
                    if(i < 4) {
                        board[i + 2][j].cangoto[up2] = false;
                    }
                }
                if(i > 0) {
                    board[i - 1][j].cangoto[down1] = false;
                    board[i - 1][j].cangoto[down2] = true;
                    if(i > 1) {
                        board[i - 2][j].cangoto[down2] = false;
                    }
                }
            }
        }
    }
    inf.clear();
    inf.seekg(0);

    for(i = 0; i < 6; i++) {
        for(j = 0; j < 6; j++) {
            inf >> x;
            if(x == 'r') {
                if(j < 5) {
                    board[i][j + 1].cangoto[left1] = false;
                    board[i][j + 1].cangoto[left2] = false;
                    if(j < 4) {
                        board[i][j + 2].cangoto[left2] = false;
                    }
                }
                if(j > 0) {
                    board[i][j - 1].cangoto[right1] = false;
                    board[i][j - 1].cangoto[right2] = false;
                    if(j > 1) {
                        board[i][j - 2].cangoto[right2] = false;
                    }
                }

                if(i < 5) {
                    board[i + 1][j].cangoto[up1] = false;
                    board[i + 1][j].cangoto[up2] = false;
                    if(i < 4) {
                        board[i + 2][j].cangoto[up2] = false;
                    }
                }
                if(i > 0) {
                    board[i - 1][j].cangoto[down1] = false;
                    board[i - 1][j].cangoto[down2] = false;
                    if(i > 1) {
                        board[i - 2][j].cangoto[down2] = false;
                    }
                }
                break;
            }
        }
    }
}

void doPP(vector<coord>& pp){
    pp.resize(4);
    coord temp;
    temp.i=5;
    temp.j=5;
    pp[0]=temp;
    temp.i=4;
    temp.j=4;
    pp[1]=temp;
    temp.i=4;
    temp.j=5;
    pp[2]=temp;
    temp.i=5;
    temp.j=4;
    pp[3]=temp;
}

void setEdgeBounds(vector<vector<square> >& b){
    int i;
    for(i=0;i<6;i++){
        b[i][0].cangoto[left1]=false;
        b[i][0].cangoto[left2]=false;
        b[i][1].cangoto[left2]=false;
        
        b[i][5].cangoto[right1]=false;
        b[i][5].cangoto[right2]=false;
        b[i][4].cangoto[right2]=false;
        
        b[0][i].cangoto[up1]=false;
        b[0][i].cangoto[up2]=false;
        b[1][i].cangoto[up2]=false;
        
        b[5][i].cangoto[down1]=false;
        b[5][i].cangoto[down2]=false;
        b[4][i].cangoto[down2]=false;
    }
}

void setInitialGoTo(vector<vector<square> >& b){
    //i is dowm
    //j is right
    b[4][3].cangoto[right1]=false;
    b[4][3].cangoto[right2]=false;
    b[4][2].cangoto[right2]=false;
    b[5][3].cangoto[right1]=false;
    b[5][3].cangoto[right2]=false;
    b[5][2].cangoto[right2]=false;
    b[4][4].cangoto[right1]=false;
    b[5][4].cangoto[right1]=false;
    
    b[4][5].cangoto[left1]=false;
    b[5][5].cangoto[left1]=false;
    
    b[3][4].cangoto[down1]=false;
    b[3][4].cangoto[down2]=false;
    b[2][4].cangoto[down2]=false;
    b[3][5].cangoto[down1]=false;
    b[3][5].cangoto[down2]=false;
    b[2][4].cangoto[down2]=false;
    b[4][4].cangoto[down1]=false;
    b[4][5].cangoto[down1]=false;
    
    b[5][4].cangoto[up1]=false;
    b[5][5].cangoto[up1]=false;
}
int main() {
    ifstream inf("corners.in");
    ofstream ouf("corners.out");

    int i;
    vector<vector<square> > board;
    vector<coord> pp;
    vector<vector<bool> > visited;
    
    board.resize(6);
    visited.resize(6);
    for(i = 0; i < 6; i++) {
        visited[i].resize(6);
        board[i].resize(6);
    }

    readBoard(inf, board);
    setEdgeBounds(board);//sets (e.g.) cangoto[left] of [0][0] to false because there is boundary
    setInitialGoTo(board);//sets going to squares where the pouls are to false
    
    //setup for dfs
    mind=9999;
    visited[4][4]=true;
    visited[4][5]=true;
    visited[5][5]=true;
    visited[5][4]=true;
    doPP(pp);//initialise polpos vector to bottom right corner
    
    dfs(board,pp,0,visited);
    
    ouf<<mind<<endl;
    
    inf.close();
    ouf.close();
    return 0;
}
