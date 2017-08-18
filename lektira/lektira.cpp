#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ret[51];

void rev(char str[],int from,int to){
	int i;
	int j=0;
	for(i=to;i>=from;i--){
		ret[j]=str[i];
		j++;
	}
	ret[j]='\0';
}

int main(){
	freopen("lektira.in","r",stdin);
	freopen("lektira.out","w",stdout);


	char wrd[51];
	scanf("%s",wrd);

	int l=strlen(wrd);
	int i,j;
	char first[50],second[50],third[50],s1[50],s2[50],s3[50],min[51]={"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz"},cat[51];

	for(i=0;i<l-2;i++){
		for(j=i+1;j<l-1;j++){
			rev(wrd,0,i);
			strcpy(first,ret);
			rev(wrd,i+1,j);
			strcpy(second,ret);
			rev(wrd,j+1,l-1);
			strcpy(third,ret);


			strcpy(s1,first);  

			strcpy(s2,second);  
			strcpy(s3,third);  

			cat[0]='\0';
			strcat(cat,s1);
			strcat(cat,s2);
			strcat(cat,s3);
			if(strcmp(cat,min)<0){
				strcpy(min,cat);
			}
		}
	}

	printf("%s\n",min);
	return 0;
}

