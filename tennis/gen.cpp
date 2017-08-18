//#include<fstream>
//#include<vector>
//#include<string.h>
//#include<random>
//
//using namespace std;
//int main(){
//    ofstream fout("tmp_tourns.txt");
//    int i,j,k,s=0;;
//    vector<int> tour;
//    int level;
////    for(level=2;level<=100;level++){
////        tour.resize(level);
////        s=0;
////        for(i=0;i<level-1;i++){
////            for(j=i+1;j<level;j++){
////                fout<<level<<" ";
////                tour[i]++;
////                tour[j]++;
////                s=0;
////                for(k=0;k<level;k++){
////                    fout<<tour[k]<<" ";
////                    s+=tour[k];
////                }
////                fout<<endl;
////            }
////        }
////        tour.clear();
////    }
//    tour.resize(7);
//    for(j=0;j<500;j++){
//        for(i=0;i<7;i++){
//            tour[i]=rand()%8;
//        }
//        fout<<"7 ";
//        for(k=0;k<7;k++){
//            fout<<tour[k]<<" ";
//        }
//        fout<<endl;
//    }
//    fout<<endl;
//    fout.close();
//    
//    char buf[10000];
//    ifstream fin("tmp_tourns.txt");
//    ofstream fout2("valid_tourns.txt");
//    while(!fin.eof()){
//        fin.getline(buf,10000);
//        for(i=0;i<strlen(buf)-1;i++){
//            if((buf[i]==' ')&&(buf[i+1]=='0')){
//                break;
//            }
//        }if(i==strlen(buf)-1){
//            fout2<<buf<<endl;
//        }
//    }
//    fin.close();
//    fout2.close();
//    return 0;
//}