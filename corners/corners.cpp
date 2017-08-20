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

void readBoard(ifstream& inf, vector<vector<square> >& board){
    int i,j,k;
    char x;
    //read the board from stdin
    //+ is right/down
    for(i = 0; i < 6; i++) {
        for(j = 0; j < 6; j++) {
            for(k=0;k<8;k++){
                board[i][j].cangoto[k]=true;
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

int main() {
    ifstream inf("corners.in");
    ofstream ouf("corners.out");

    int i;
    vector<vector<square> > board;

    board.resize(6);
    for(i = 0; i < 6; i++) {
        board[i].resize(6);
    }

    readBoard(inf,board);
    
    inf.close();
    ouf.close();
    return 0;
}
