#include<stdio.h>
#include<stdlib.h>
//         ..............................             .N?                         
//          .         ..   .         ....  .         MM $M .           .   .     .
//             MM   MMM.   .           ......    .. MM...M...    ..  ........  . .
//         ...M.       M?. ..        ........    . MMM ..M...    . ..........    .
//           M         .8M             ......    .M..M ..M...    .   ........    .
//          MM   MM MMM.  M$            .........M ..M ..M.....................  .
//.. ..    .M .  M  ...MI .MM ...........     .MM    M   MN                    . .
//.. ...   .M.. MM  . ..MM.  M,  . . .. .    MM     M~   .M                       
//..   .    MM. MM ......MM...DDDDD.                      MZ                      
//..  .     MM.MM., . . ..M..        ..                   .M                    . 
//.. .     .MM.MM.MMMMMM .:M      .  ..                    +MM.                   
//.. ..    .M .MM.MMMMMM...M............                      MMM                 
//..  ..   .MM.MM .MMMMM  . .        ..                         .MMM.             
//........ ..M8MM  .MMMMM ... . .. ......                          .MM            
//.. ...   ..M8. . ..IMMM.... .. . .....                             N7           
//.. ..    ..MD. M ....$.................                             M           
//.. ...   .M............................                  .MM.       M          .
//.. ...   M ............................               .MMMMMM.      M          .
//..  .   M . ..   .... ... . ... . ... ..               MMMMMMM.     MM          
//..  .   M.. ..   .......... . . . .,MMMMMM              MMMMMM      .M.         
//.. .    M.....  ... . . . .       MMMMMM .MM             MMMM,       ,M         
//.. ..   M.....   .......... .. . .MMMMMM  MMM                         M.        
//..  .. MM. ...    . . . . .        MMMMM ?MM                           M        
//.......M ....    .......... . .. ....MMMMM                             MM.      
//   ...7?..                               .           . MMMMMMMMMM7   .  M+     .
//  ....M...                               .            $M?MMMMMMMMMM.    .M     .
//  ...M? ..                             .....   .. . ..$MMMMMMMMMMMM .....M ... .
//    .M  ..                               .           . MMMMMMMMMM M  .   ?M    .
//    MM. .                                .           . MMMMMMMMMMM   .   .M.   .
//   :M . ..                               ..        ..   .MMMMMMMMM  .    .MM   .
//   M.....                                .     .   . .?  +MMMMMM.M . .   ..M.  .
//  .I. . .   N                            .         ..    MMM+,MD.MM      ..M   .
//  M.......  M                                  .   .M.   MM.MMMMMM . .     M.  .
//  M .....   ~M                           .  M..       7MMMMMMMMMMMM  .   .NM   .
// MM .....    M.                          .   ?MMMMMMMMMMMMMMMMMMM    .   .M.   .
// M .......  .MM.                         .       .77MMMMMMMMMMMM         Z.    .
// M ..... M.  .M                        .....   .. . ......  .  .. . .....M.... .
// M  . . .MM                              .           .   .           .  M      .
// M  . . . .MM                            .           .   .           . .M.     .
// M  . . ..  MM                           ..         .    ..         . .MD..    .
// M  ...MM    .M                          .     .   . .   .     .   ..M?M .  .  .
// M  . . ,MN.                             .               .           M.M .     .
// MM ...... MM                                  .   . .         .   .M. M    .  .
// .M .....   ..M                    .     .           .   .       .MN . M .     .
// .M .....                           MMM  .           .   .     MMM   .  M.     .
// .M.......                             7MMI.             . IMM7.        M8     .
//  M.......                             ...  MMM ... ... MMM.   .. . .....M.... .
// MM . . ..                               .      MMMMMMMM .           .    M    .
//.M  ... ..                                .    .   ...    .    .   ...    M    .
//.M  .    ..    .                                                          MM    
//.M ........ . . . ...     .        .. . ...... . ...... ...... . ...... ...M.   
                         
//such amaze
//           very code
//  much recursion
//         wow

typedef struct road{
	int from,to,weight;
}road;

typedef struct crossings{
	int sum,branches;
}crossings;

void countBranches(crossings node[],road route[],int numofnodes){
	int i,j;
	for(i=0;i<numofnodes;i++){
		node[i].branches=0;
		node[i].sum=0;
	}
	for(i=0;i<numofnodes;i++){
		for(j=0;j<numofnodes-1;j++){
			if(route[j].from==i+1){
				node[i].branches++;
			}
		}
	}
}

void dfs(road route[],crossings node[],int nodenum,int numofnodes){
	if(node[nodenum].branches==0){
		for(int j=0;j<numofnodes-1;j++){
			if(route[j].to==nodenum+1){
				node[nodenum].sum=route[j].weight+node[route[j].from-1].sum;
				break;
			}
		}
	}else{
		for(int j=0;j<numofnodes-1;j++){
			if(route[j].from==nodenum+1){//find next node
				for(int k=0;k<numofnodes-1;k++){
					if(route[k].to==nodenum+1){
						node[nodenum].sum=route[k].weight+node[route[k].from-1].sum;
						break;
					}
				}
				dfs(route,node,route[j].to-1,numofnodes);//do the thing again in the next node
			}
		}
	}
}

int main(){
	FILE* in=fopen("contest.in","r");
	FILE* out=fopen("contest.out","w");
	int numofnodes;
	fscanf(in,"%d",&numofnodes);

	int max=0;
	int i,j;

	road *route=new road[numofnodes-1];
	crossings* node=new crossings[numofnodes];

	for(i=0;i<numofnodes-1;i++){
		fscanf(in,"%d%d%d",&route[i].from,&route[i].to,&route[i].weight);
	}

	countBranches(node,route,numofnodes);

	dfs(route,node,0,numofnodes);

	for(i=0;i<numofnodes;i++){
		if(node[i].sum>max){
			max=node[i].sum;
		}
	}
	fprintf(out,"%d\n",max);
	fclose(in);
	fclose(out);
	return 0;
}
