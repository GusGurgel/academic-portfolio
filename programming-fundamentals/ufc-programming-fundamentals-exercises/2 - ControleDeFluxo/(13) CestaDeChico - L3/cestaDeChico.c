#include <stdio.h>

int main(int argc, char **argv)
{
	//Capacidade da cesta tem que ser maior que o total de
	//frutas, se não ele vai ter que ir mais de uma vez.
	
	int voltas, totalFrutas,capCesta, contBananas, contGoiabas, contMangas;
	
	scanf("%d\n%d\n%d\n%d", &capCesta, &contBananas, &contGoiabas, &contMangas);
	
	totalFrutas = contBananas + contGoiabas + contMangas;
	
	if(!(totalFrutas == capCesta)){
		voltas = (totalFrutas / capCesta);
		if( (totalFrutas % capCesta) == 0 ){
			printf("%d", voltas * 1);
		}else{
			printf("%d", (voltas * 1) + 1);
		}
	}else{
		voltas = 1;
		//Voltas vezes 1 minuto
		printf("%d", voltas * 1);
	}
	
	return 0;
}

