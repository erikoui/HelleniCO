//solves hellenico corners problem by modified flood fill

//#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>

#define flag 2
#define rock 1
#define empty 0

using namespace std;



int main() {
    ifstream inf("corners.in");
    ofstream ouf("corners.out");
    int i, j, k, l;
    const int initval = 1337;
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

    dist[4][4][0]=0;
    dist[4][5][1]=0;
    dist[5][4][2]=0;
    dist[5][5][3]=0;
    const int maxdist = 4;
    int currdist = 0;
    int shitloadoftimes;
    int asd;
    for(asd=0;asd<100;asd++){
    for(shitloadoftimes = 0; shitloadoftimes < 300; shitloadoftimes++) {
        for(k = 0; k < 4; k++) {
            for(i = 0; i < 6; i++) {
                for(j = 0; j < 6; j++) {
                    if(dist[i][j][k] == currdist) {
                        if((j >= 1)   //                                  can i go left 1?
                                && ((board[i][j - 1] == empty)) //              and nothing there
                                && ((dist[i][j - 1][k] > currdist + 1))) { //  and not been there
                            dist[i][j - 1][k] = currdist + 1;
                            i--;
                            break;
                        }

                        if((j >= 2) &&  //                                can i go right 2?
                                (board[i][j - 2] == empty) && //                and 2 sq up is empty
                                (board[i][j - 1] != flag) && //                and no flag 1 sq up
                                ((dist[i][j - 1][(k + 1) % 4] < currdist + 1 + maxdist) ||
                                 (dist[i][j - 1][(k + 2) % 4] < currdist + 1 + maxdist) ||
                                 (dist[i][j - 1][(k + 3) % 4] < currdist + 1 + maxdist)) &&
                                (dist[i][j - 2][k] > currdist + 1)) { //       and not already visited
                            dist[i][j - 2][k] = currdist + 1;
                            i--;
                            break;
                        }

                        if((j <= 4)   //                                  can i go left 1?
                                && ((board[i][j + 1] == empty)) //              and nothing there
                                && ((dist[i][j + 1][k] > currdist + 1))) { //  and not been there
                            dist[i][j + 1][k] = currdist + 1;
                            i--;
                            break;
                        }

                        if((j <= 3) &&  //                                can i go right 2?
                                (board[i][j + 2] == empty) && //                and 2 sq up is empty
                                (board[i][j + 1] != flag) && //                and no flag 1 sq up
                                ((dist[i][j + 1][(k + 1) % 4] < currdist + 1 + maxdist) ||
                                 (dist[i][j + 1][(k + 3) % 4] < currdist + 1 + maxdist) ||
                                 (dist[i][j + 1][(k + 2) % 4] < currdist + 1 + maxdist)) &&
                                (dist[i][j + 2][k] > currdist + 1)) { //       and not already visited
                            dist[i][j + 2][k] = currdist + 1;
                            i--;
                            break;
                        }

                        if((i >= 1)   //                                  can i go left 1?
                                && ((board[i - 1][j] == empty)) //              and nothing there
                                && ((dist[i - 1][j][k] > currdist + 1))) { //  and not been there
                            dist[i - 1][j][k] = currdist + 1;
                            i-=2;
                            break;
                        }

                        if((i >= 2) &&  //                                can i go right 2?
                                (board[i - 2][j] == empty) && //                and 2 sq up is empty
                                (board[i - 1][j] != flag) && //                and no flag 1 sq up
                                ((dist[i - 1][j][(k + 1) % 4] < currdist + 1 + maxdist) ||
                                 (dist[i - 1][j][(k + 2) % 4] < currdist + 1 + maxdist) ||
                                 (dist[i - 1][j][(k + 3) % 4] < currdist + 1 + maxdist)) &&
                                (dist[i - 2][j][k] > currdist + 1)) { //       and not already visited
                            dist[i - 2][j][k] = currdist + 1;
                            i-=3;
                            break;
                        }

                        if((i <= 4)   //                                  can i go left 1?
                                && ((board[i + 1][j] == empty)) //              and nothing there
                                && ((dist[i + 1][j][k] > currdist + 1))) { //  and not been there
                            dist[i + 1][j][k] = currdist + 1;
                            break;
                        }

                        if((i <= 3) &&  //                                can i go right 2?
                                (board[i + 2][j] == empty) && //                and 2 sq up is empty
                                (board[i + 1][j] != flag) && //                and no flag 1 sq up
                                ((dist[i + 1][j][(k + 1) % 4] < currdist + 1 + maxdist) ||
                                 (dist[i + 1][j][(k + 3) % 4] < currdist + 1 + maxdist) ||
                                 (dist[i + 1][j][(k + 2) % 4] < currdist + 1 + maxdist)) &&
                                (dist[i + 2][j][k] > currdist + 1)) { //       and not already visited
                            dist[i + 2][j][k] = currdist + 1;
                            i++;
                            break;
                        }
                    }
                }
            }
        }
        currdist++;
    }currdist=0;
    }
    
    int tst[]={0,1,2,3};  
    int sum=1243123;  
    int sum1;  
  
    for (i=0; i<240; i++) { //brute force the minimum sum of the 4 down right squares  
        sum1=dist[0][0][tst[0]]+dist[0][1][tst[1]]+dist[1][0][tst[2]]+dist[1][1][tst[3]];  
        next_permutation(tst,tst+4);  
        if (sum1<sum) {  
            sum=sum1;  
        }  
    }  
    //main idea is to calculate minimum distance from each point in 0,0 to 1,1 using dynamic programming(find min distance to known point and add to that to find min distance to e.g 0,0)  
  
    if (sum>100)  
        sum=-1; 
        
    ouf<<sum<<endl;
    return 0;

}
