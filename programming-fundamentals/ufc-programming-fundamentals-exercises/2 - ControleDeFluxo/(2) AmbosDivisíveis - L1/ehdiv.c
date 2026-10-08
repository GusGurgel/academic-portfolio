#include <stdio.h>

int main(){
    
    int val1, val2;
    
    scanf("%d %d", &val1, &val2);
    
    if( ( ((val1 % 5) == 0) && ((val2 % 5) == 0)) || (((val1 % 3) == 0) && ((val2 % 3) == 0)) ){
        printf("sim");
    }else{
        printf("nao");
    }
    
   return 0; 
}
