/*entrada é x valor correspondente ao
 * ultron e n é a quantidade de elementos 
 * na sequência
 * */
#include <stdio.h>

int main()
{
	int nUltron, nElem, x, repete = 0;
	scanf("%d %d", &nUltron, &nElem);
	

	while(nElem > 0)
	{
		nElem--;
		scanf("%d", &x);
		if(x == nUltron)
		{
			repete++;
		}
	}
	printf("%d", repete);
	return 0;
}

