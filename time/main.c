    #include <stdio.h>    
    #include <stdlib.h>    
        
    int main(){    
    int deft,hr,min,sec;;                        
    FILE *in=fopen("time.in","r");            
    FILE *out=fopen("time.out","w");          
    char inp[10];     
    char h[]={' ',' ',' '};    
    char m[]={' ',' ',' '};    
    char s[]={' ',' ',' '};                         
        fscanf(in,"%s",inp);    
        h[0]=inp[0];    
        h[1]=inp[1];    
        h[2]='\0';    
        m[2]='\0';    
        s[2]='\0';    
        m[0]=inp[3];    
        m[1]=inp[4];    
        s[0]=inp[6];    
        s[1]=inp[7];    
        hr=2*atoi(h);    
        min=2*atoi(m);    
        sec=2*atoi(s);    
        if(sec>=60){    
            min++;    
            sec=(sec%60);    
        }      
        if(min>=60){    
            hr++;    
            min=(min%60);    
        }    
        //    
        if(hr<10){    
             fprintf(out,"0%d",hr);      
         }    
         else    
          fprintf(out,"%d",hr);    
          //      
         if(min<10){    
             fprintf(out,":0%d",min);      
         } else    
          fprintf(out,":%d",min);      
          //    
         if(sec<10){    
             fprintf(out,":0%d",sec);      
        }    
         else    
          fprintf(out,":%d",sec);      
                       
                      
        fprintf(out,"\n");    
        fclose(in);    
        fclose(out);    
        return(0);    
    }    
