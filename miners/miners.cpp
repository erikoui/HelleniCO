#include <fstream>
#include <iostream>
#include <ctime>
#include <vector>
#include <stdlib.h>
#include <chrono>

using namespace std;

typedef struct mines {
    vector<char> m1, m2;
    int s1, s2;
} mines;

mines minebuf;

int s1, s2, s3, s4;
int tmpsum1, tmpsum2;

int diversity(char a, char b, char c)
{
    return ((a == b) && (b == c)) ? 1 : ((a != b) && (a != c)) ? b == c ? 2 : 3 : 2;
}

int calc(vector<char>& m1, vector<char>& m2)
{
    int i, sum = 0;
    int s1 = m1.size();
    int s2 = m2.size();

    for(i = 0; i < s1; ++i) {
        (i > 1) ? sum += diversity(m1[i], m1[i - 1], m1[i - 2]) : (i == 0) ? ++sum : (m1[i] == m1[i - 1]) ? ++sum :
                                                                                                            sum += 2;
    }
    for(i = 0; i < s2; ++i) {
        (i > 1) ? sum += diversity(m2[i], m2[i - 1], m2[i - 2]) : (i == 0) ? ++sum : (m2[i] == m2[i - 1]) ? ++sum :
                                                                                                            sum += 2;
    }
    return sum;
}
int calc(vector<char>& m1)
{
    int i, sum = 0;
    s1 = m1.size();

    for(i = 0; i < s1; ++i) {
        (i > 1) ? sum += diversity(m1[i], m1[i - 1], m1[i - 2]) : (i == 0) ? ++sum : (m1[i] == m1[i - 1]) ? ++sum :
                                                                                                            sum += 2;
    }
    return sum;
}

void put_next_char_in_2_minecases(vector<mines>& minecases, int i, char fooditem, int& max)
{
    if((minecases[i].m1.size() < 2) ||
        (minecases[i].m2.size() < 2)) { // one of the mines has 0 or 1 in it, cant do optimisation
        minebuf = minecases[i];

        minebuf.m1.push_back(fooditem); // put cur into first mine
        if((minebuf.m1.size() < 3) || (minebuf.m2.size() < 3)) {
            tmpsum1 = calc(minebuf.m1);
            tmpsum2 = calc(minebuf.m2);
        } else { // both mines have 3 or more items(including the new one)
            tmpsum1 = minecases[i].s1 + diversity(*(minebuf.m1.end() - 3), *(minebuf.m1.end() - 2), fooditem);
            tmpsum2 = minecases[i].s2;
        }
        if(tmpsum1 + tmpsum2 > max) {
            max = tmpsum1 + tmpsum2;
            minebuf.s1 = tmpsum1;
            minebuf.s2 = tmpsum2;
            minecases.push_back(minebuf);
        } else if(tmpsum1 + tmpsum2 > max - 2) {
            minebuf.s1 = tmpsum1;
            minebuf.s2 = tmpsum2;
            minecases.push_back(minebuf);
        }

        minebuf.m1.pop_back(); // take it out

        minebuf.m2.push_back(fooditem);
        if((minebuf.m1.size() < 3) || (minebuf.m2.size() < 3)) {
            tmpsum2 = calc(minebuf.m2);
            tmpsum1 = calc(minebuf.m1);
        } else {
            tmpsum2 = minecases[i].s2 + diversity(*(minebuf.m2.end() - 3), *(minebuf.m2.end() - 2), fooditem);
            tmpsum1 = minecases[i].s1;
        }
        if(tmpsum1 + tmpsum2 > max) {
            max = tmpsum1 + tmpsum2;
            minebuf.s1 = tmpsum1;
            minebuf.s2 = tmpsum2;
            minecases.push_back(minebuf);
        } else if(tmpsum1 + tmpsum2 > max - 2) {
            minebuf.s1 = tmpsum1;
            minebuf.s2 = tmpsum2;
            minecases.push_back(minebuf);
        }
    } else { // both mines have 2 or more items

        minebuf = minecases[i];
        char m0;
        // minebuf.m1.push_back(fooditem); // put cur into first mine
        tmpsum1 = minecases[i].s1 + diversity(*(minebuf.m1.end() - 2), *(minebuf.m1.end() - 1), fooditem);
        tmpsum2 = minecases[i].s2;
        m0 = *(minebuf.m1.end() - 2); // save penultimate so that it can be restored later
        *(minebuf.m1.end() - 2) = *(minebuf.m1.end() - 1); // move last item to penultimate position
        *(minebuf.m1.end() - 1) = fooditem; // put new thing to last position

        if(tmpsum1 + tmpsum2 > max) {
            max = tmpsum1 + tmpsum2;
            minebuf.s1 = tmpsum1;
            minebuf.s2 = tmpsum2;
            minecases.push_back(minebuf);
        } else if(tmpsum1 + tmpsum2 > max - 2) {
            minebuf.s1 = tmpsum1;
            minebuf.s2 = tmpsum2;
            minecases.push_back(minebuf);
        }

        // minebuf.m1.pop_back(); // take it out
        *(minebuf.m1.end() - 1) = *(minebuf.m1.end() - 2); // undo move last item to penultimate position
        *(minebuf.m1.end() - 2) = m0; // undo save penultimate so that it can be restored later

        // minebuf.m2.push_back(fooditem);
        tmpsum2 = minecases[i].s2 + diversity(*(minebuf.m2.end() - 2), *(minebuf.m2.end() - 1), fooditem);
        tmpsum1 = minecases[i].s1;
        *(minebuf.m2.end() - 2) = *(minebuf.m2.end() - 1); // move last item to penultimate position
        *(minebuf.m2.end() - 1) = fooditem; // put new thing to last position

        if(tmpsum1 + tmpsum2 > max) {
            max = tmpsum1 + tmpsum2;
            minebuf.s1 = tmpsum1;
            minebuf.s2 = tmpsum2;
            minecases.push_back(minebuf);
        } else if(tmpsum1 + tmpsum2 > max - 2) {
            minebuf.s1 = tmpsum1;
            minebuf.s2 = tmpsum2;
            minecases.push_back(minebuf);
        }
    }
}

void first_put_next_char_in_2_minecases(vector<mines>& minecases, char fooditem, int& max)
{
    minebuf.m1.push_back(fooditem); // put cur into first mine
    max = 1;
    minebuf.s1 = 1;
    minebuf.s2 = 0;

    minecases.push_back(minebuf);

    minebuf.m1.pop_back(); // take it out
    minebuf.m2.push_back(fooditem);
    minebuf.s1 = 0;
    minebuf.s2 = 1;
    minecases.push_back(minebuf);
}

bool nosameafterthiswithbettersum(vector<mines>& minecases,
    vector<mines>::iterator cur,
    vector<vector<mines>::iterator>& delet)
{
    vector<mines>::iterator i;

    s3 = cur->m1.size() - 1;
    s4 = cur->m2.size() - 1;
    if((s3 < 1) || (s4 < 1)) {
        return true;
    }
    i = cur + 1;
    while(i != minecases.end()) {
        s1 = i->m1.size() - 1;
        s2 = i->m2.size() - 1;
        if((s1 < 1) || (s2 < 1)) {
            return true;
        }
        if((*(i->m1.end() - 1) == *(cur->m1.end() - 1)) && (*(i->m1.end() - 2) == *(cur->m1.end() - 2)) &&
            (*(i->m2.end() - 1) == *(cur->m2.end() - 1)) &&
            (*(i->m2.end() - 2) == *(cur->m2.end() - 2))) { // if last 2 chars are same
            if((i->s1 + i->s2) >= (cur->s1 + cur->s2)) {
                return false;
            } else {
                minecases.erase(i);
            }
        } else {
            ++i;
        }
    }

    return true;
}

int main(int argc, char** argv)
{
    auto t1 = chrono::high_resolution_clock::now();
    vector<mines> minecases, minecases2;
    vector<mines>::iterator it;
    vector<mines> cleanmine;
    vector<vector<mines>::iterator> delet;
    int max = 0;
    unsigned int s;
    char* food = new char[100001];
    unsigned int nchars, i, j;
    FILE* fin = fopen("miners.in", "r");
    ofstream fout("miners.out");

    // read miners.in////////////////////////
    fscanf(fin, "%d", &nchars); // get number of chars
    food[0] = fgetc(fin);       // skip the /n
    for(i = 0; i < nchars; i++) {
        food[i] = fgetc(fin); // get each char
    }
    /////////////////////////////////////////

    first_put_next_char_in_2_minecases(minecases, food[0], max);
    s = 2;
    for(i = 1; i < nchars; ++i) {
        for(j = 0; j < s; ++j) { // for each minecase
            put_next_char_in_2_minecases(minecases, j, food[i], max);
        }

        it = minecases.begin() + s;
        s = 0;
        delet.clear();
        cleanmine.clear();
        while(it != minecases.end()) {
            if((it->s1 + it->s2 > max - 2) && (nosameafterthiswithbettersum(minecases, it, delet))) {
                cleanmine.push_back(*it);
                ++s;
            }
            ++it;
        }

        ++i;
        if(i < nchars) {
            for(j = 0; j < s; ++j) { // for each minecase
                put_next_char_in_2_minecases(cleanmine, j, food[i], max);
            }

            it = cleanmine.begin() + s;
            s = 0;
            delet.clear();
            minecases.clear();
            for(; it != cleanmine.end(); ++it) {
                if((it->s1 + it->s2 > max - 2) && (nosameafterthiswithbettersum(cleanmine, it, delet))) {
                    minecases.push_back(*it);
                    ++s;
                }
            }
        }
    }

    auto t2 = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> fp_ms = t2 - t1;
    cout << "\r" << i << ":" << minecases.size() << "    " << fp_ms.count() << "                               ";
    cout << endl << max;
    fout << max << endl;
}
