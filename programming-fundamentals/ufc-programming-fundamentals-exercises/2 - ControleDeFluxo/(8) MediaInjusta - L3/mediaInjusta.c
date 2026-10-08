#include <stdio.h>

int main()
{
	/*Média injusta
	 * 1. Pegar de 3 notas, as duas melhores
	 * 2. Pegar a soma das duas notas mais a nota do trabalho
	 * 3. Dizer se o aluno passou com média maior ou igual a 7 ou
	 * sé o aluno vai para recuperação final com nota menor que 7
	 * */
	 
	 int n1, n2, n3, trabalho, media;
	 
	 scanf("%d %d %d %d", &n1, &n2, &n3, &trabalho);
	 
	 media = trabalho;
	 
	 if( ((n1 + n2) >= (n1 + n3)) && ((n1 + n2) >= (n2 + n3))  ){
		media += (n1 + n2) ; 
	 }else if(((n1 + n3) >= (n1 + n2)) && ((n1 + n3) >= (n2 + n3))){
		media += (n1 + n3) ;
	 }else{
		media += (n3 + n2) ;
	 }
	 
	 media = (media / 3);
	 
	 if(media >= 7){
		printf("Aprovado com %d", media);
	 }else{
		printf("Final com %d", media);
	 }
	 
	return 0;
}

