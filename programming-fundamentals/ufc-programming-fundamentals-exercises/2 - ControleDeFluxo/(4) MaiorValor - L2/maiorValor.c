#include <stdio.h>

int main(){
    
    int val1, val2, val3, val4;
    int maiorAtual;
    
    scanf("%d %d %d %d", &val1, &val2, &val3, &val4);
    
    if(val1 > val2){
        maiorAtual = val1;
    }else{
        maiorAtual = val2;
    }
    
    if(maiorAtual < val3)
    {
        maiorAtual = val3;
    }
    
    if(maiorAtual < val4){
        maiorAtual = val4;
    }
    
    printf("%d", maiorAtual);
    
   return 0; 
}
