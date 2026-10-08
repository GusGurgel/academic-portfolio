#include <stdio.h>

int main()
{
	//Ajuda ao vendedor
	//totalPagar * 0.9 Desconto de 10%
	//totalPagar / 3 Valor em três parcelas
	//(totalPagar * 0.9 Desconto de 10%) * 0.05
	//totalPagar * 0.05
	
	float totalPagar;
	
	scanf("%f", &totalPagar);
	
	
	printf("%0.2f\n", (totalPagar * 0.9) );
	
	printf("%0.2f\n", (totalPagar / 3.0) );
	
	printf("%0.2f\n", ((totalPagar * 0.9) * 0.05) );
	
	printf("%0.2f", (totalPagar * 0.05) );
	
	return 0;
}

