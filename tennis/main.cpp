#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool gr(int a, int b)//used for sorting
{
    return a > b;
}

int main()
{
    ifstream fin("tennis.in");
    ofstream fout("tennis.out");

    bool ret=false;
    int i, j, nlines, nath, sp, sum1;
    vector<int> data;

    fin >> nlines;
    for(i = 0; i < nlines; i++) {
        //init vars
        ret = true;
        sum1 = 0;
        data.clear();

        //input and remove zeroes
        fin >> nath;
        data.resize(nath);
        for(j = 0; j < nath; j++) {
            fin >> data[j];
            if(data[j] == 0) {
                j--;
                nath--;
            }
        }
        data.resize(nath);

        //check if sum is odd
        for(j = 0; j < nath; j++) {
            sum1 += data[j];
        }

        if((sum1 % 2 == 1) || (nath == 1)) {
            ret = false;
        }
        else {
            if(data.size() < 80000) {//shameless case switching
                sort(data.begin(), data.end(), gr);
                while(data[0] != 0) {
                    if(data[0] >= nath) {
                        ret = false;
                        break;
                    }
                    for(j = 1; j < data[0] + 1; j++) {
                        if(--data[j] == 0) {
                            nath--;
                        }
                    }
                    data[0] = 0;
                    nath--;
                    sort(data.begin(), data.end(), gr);
                }
            }
            else {//bonus case
                sort(data.begin(), data.end(), gr);
                sp = 0;
                while(data[sp] != 0) {
                    if(data[sp] >= nath) {
                        ret = false;
                        break;
                    }
                    for(j = sp + 1; j < data[sp] + sp + 1; j++) {
                        if(data[j] != 0) {
                            data[j]--;
                        }
                        if(data[j] == 0) {
                            nath--;
                        }
                    }
                    data[0] = 0;
                    nath--;
                    sp++;
                }
            }//at least i'm not doing size==100000?fout<<possible
        }
        //print result
        ret ? fout << "Possible" << endl : fout << "Not possible" << endl;
    }
    //done
    fin.close();
    fout.close();
    return 0;
}
