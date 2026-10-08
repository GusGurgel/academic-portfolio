#include <stdio.h>

int main()
{
    int valor, mil, cen, dez, uni;
    
    scanf("%d", &valor);
    
    mil = valor / 1000;
    cen = (valor % 1000) / 100;
    dez = ((valor % 1000) % 100) / 10;
    uni = (((valor % 1000) % 100) % 10); 
    
    printf("%d\n%d\n%d\n%d\n", mil, cen, dez, uni);
    
    
}
