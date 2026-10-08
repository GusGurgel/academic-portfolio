#include <stdio.h>

int main()
{
	int valorProd, chute1, chute2, dist1, dist2;
	
	scanf("%d %d %d", &valorProd, &chute1, &chute2);
	
	dist1 = valorProd - chute1;
	dist2 = valorProd - chute2;
	
	//Pegar módulo da distância entre o chute e o valor real do pruduto
	if(dist1 < 0) { 
		dist1 = dist1 * -1 ; 
	}
	if(dist2 < 0) { 
		dist2 = dist2 * -1 ; 
	}
	
	if(dist1 != dist2){
		if(dist1 < dist2){
		printf("primeiro");
		}else{
		printf("segundo");
		}
	}else{
		printf("empate");
	}
	
	return 0;
}
