#include <stdio.h>

int main(){
    
    int val = 0;
    
    scanf("%d", &val);
    
    if(val > 0){
        //Positivo    
        printf("positivo");
    }
    if(val < 0){
        //Negativo
        printf("negativo");
    }
    if(val == 0){
        //Nulo
        printf("nulo");
    }
    
    return 0; 
}
