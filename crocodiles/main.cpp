#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
	ifstream fin("crocodiles.in");
    ofstream fout("crocodiles.out");
    long n,i,k=0,count=0,max=-500;
    vector<int> events;
    int current;

    fin>>n;
    events.resize(200002);
    
    for(i=0;i<n;++i){
        fin>>current;
        events[current+100001]++;
        
        fin>>current;
        events[current+100001]--;
    }

    for(i=0;i<200002;++i){
        count+=events[i];     
        if(count>max){
            max=count;
        }
    }

    fout<<max<<endl;
    fin.close();
    fout.close();
    return 0;
}
