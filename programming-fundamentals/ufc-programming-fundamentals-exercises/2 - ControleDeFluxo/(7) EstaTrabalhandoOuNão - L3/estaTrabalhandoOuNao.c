#include <stdio.h>


int main()
{
	//Trabalha de segunda a sexta ( 8 : 0 - 11 : 59 ) ( 14 : 0 - 17 : 59 )
	//Sábado  ( 8 : 0 - 11 : 59 )
	
	/*
	 * Entrada
	 * 
	 * {(1)
	 * Dia da semana (1 = domingo, 2 = segunda, 3 = terça, 4 = quarta
	 * 5 = quinta, 6 = sexta, 7 = sábado 
	 * )
	 * }
	 * 
	 * {(2)
	 * Horas
	 * }
	 * 
	 * {(3)
	 * Minutos
	 * }
	 * 
	 * */
	
	int diaSemana, hora, minuto; 
	
	scanf("%d %d %d", &diaSemana, &hora , &minuto);

	
	if( (diaSemana > 1 && diaSemana != 7) && ((((hora >= 8) && (hora <= 11)) && (minuto <= 59)) || (((hora >= 14) && (hora <= 17)) && (minuto <= 59))) ){
		printf("SIM");
	}else if(diaSemana == 7 && ((hora >= 8) && (hora <= 11))){
		printf("SIM");
	}else{
		printf("NAO");
	}
	
	return 0;
}

