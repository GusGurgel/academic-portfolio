
#include <stdio.h>

  int main(int argc, char **argv){
	/* Entradas Caixa 1. Comprimento 2. Largura 3 Altura
	 * Entradas Janela 1. Altura 2. Largura
	 * */
	
	int cCaixa, lCaixa, aCaixa;
	int aJanela, lJanela;
	int dmMenor = 0;
	int dmMaior = 0;
	int ladoEscolhido1 = 0;
	int ladoEscolhido2 = 0;
	
	scanf("%d\n%d\n%d\n%d\n%d", &cCaixa, &lCaixa, &aCaixa, &aJanela, &lJanela);
	
	//Achar menor valor entre as dimensões da janela
	if(cCaixa == lCaixa && lCaixa == aCaixa){
		
		if(lCaixa < aJanela && lCaixa < lJanela){
			printf("S");
		}else{
			printf("N");
		}
		
	}else{
		if(aJanela != lJanela){
			if(aJanela < lJanela){
				dmMenor = aJanela;
			}else{
				dmMenor = lJanela;
			}
		}
	
		if(aJanela != dmMaior){
			dmMaior = aJanela;
		}else{
			dmMaior = lJanela;
		}
	
		if( (dmMenor - cCaixa) >= 0 ){
			ladoEscolhido1 = cCaixa;
		}else if( (dmMenor - lCaixa) >= 0){
			ladoEscolhido1 = lCaixa;
		}else if( (dmMenor - aCaixa) >- 0){
			ladoEscolhido1 = aCaixa;
		}
	
		if( (((dmMaior - cCaixa) >= 0) && cCaixa != ladoEscolhido1) ){
			ladoEscolhido2 = cCaixa;
		}else if( (((dmMaior - lCaixa) >= 0) && lCaixa != ladoEscolhido1 ) ) {
			ladoEscolhido2 = lCaixa;
		}else if( (((dmMaior - aCaixa) >= 0) && aCaixa != ladoEscolhido1) ){
			ladoEscolhido2 = aCaixa;
		}
	
		if(ladoEscolhido1 == 0 || ladoEscolhido2 == 0){
			printf("N");
		}else{
			printf("S");
		}
	}
	
	
	return 0;
}

