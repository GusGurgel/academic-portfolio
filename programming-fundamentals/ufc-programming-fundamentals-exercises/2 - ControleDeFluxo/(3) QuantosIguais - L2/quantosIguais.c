#include <stdio.h>

int main(){
    
    int val1, val2, val3;
    
    scanf("%d %d %d", &val1, &val2, &val3);
    
        
    if( (3 * val1) == (val1 + val2 + val3) ){
        printf("3");
    }else if( val1 != val2 && val2 != val3  && val3 != val1){
        printf("0");
    }else{
        printf("2");
    }
     
   return 0; 
}
