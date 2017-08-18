#include <stdio.h>  
#include <stdlib.h>  

int tabl[1000];

void swap(int first,int last){
	int temp;
	temp=tabl[first];
	tabl[first]=tabl[last];
	tabl[last]=temp;
}

bool toofulfo2(int n1,int n2){
	//check if 2 full of 2
	int i;
	for(i=n1;i<n1+n2;i++){
		if(tabl[i]!=2){
			return false;
		}
	}
	return true;
}

int main(){  
	FILE* in=fopen("sort3.in","r");  
	FILE* out=fopen("sort3.out","w");  
	int num,k;  
	int swaps=0;
	int i,j; 
	int n1=0,n2=0,n3=0;
	fscanf(in,"%d",&num); 
	for(i=0;i<num;i++){  
		fscanf(in,"%d",&tabl[i]);  
	}  
	for(i=0;i<num;i++){
		switch(tabl[i]){
			case 1:
				n1++;
				break;
			case 2:
				n2++;
				break;
			case 3:
				n3++; 
				break;
			default:
				exit(EXIT_FAILURE);
		}
	}
	bool swapped=false;
	while(!toofulfo2(n1,n2)){
		for(i=0;i<n1;i++){
			if(tabl[i]==2){
				swapped=false;
				for(j=n1;((j<(n1+n2)) && (!swapped));j++){
					if(tabl[j]==1){
						swap(i,j);
						swaps++;
						swapped=true;
						break;
					}
				}
				for(j=n1;((j<(n1+n2)) && (!swapped));j++){
					if(tabl[j]==3){
						swap(i,j);
						swaps++;
						swapped=true;
						break;
					}
				}
			}
		}
		for(i=n1+n2;i<num;i++){
			if(tabl[i]==2){
				swapped=false;
				for(j=n1;((j<(n1+n2)) && (!swapped));j++){
					if(tabl[j]==3){
						swap(i,j);
						swaps++;
						swapped=true;
						break;
					}
				}
				for(j=n1;((j<(n1+n2)) && (!swapped));j++){
					if(tabl[j]==1){
						swap(i,j);
						swaps++;
						swapped=true;
						break;
					}
				}
			}
		}
	}

	for(i=0;i<n1;i++){
		if(tabl[i]==3){
			swaps++;
		}
	}
	
	//printf("%d\n",swaps);
	fprintf(out,"%d\n",swaps);  
	fclose(in);  
	fclose(out);  
	//system("PAUSE");
	return 0;  
}  
