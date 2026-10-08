#include <stdio.h>

int main()
{
	
									    //H    M    S
	/*1.Pegar uma hora específica, exemplo 12 : 30 : 20;
	  2.Somar mais 1 segundo, exemplo 12 : 30 : 20;
	  * 
	  * 
	  * Ideia: Três vairiáveis, s, m, h. Somar s + 1, se s == 60, então, s = 0, m + 1, se m == 60,
	  * então,  m = 0, h + 1, se h == 24, então h = 0
	*/
	
	int h, m, s;
	
	scanf("%d %d %d", &h, &m, &s);
	
	s++;
	if(s == 60){
		s = 0;
		m++;
		if(m == 60){
			m = 0;
			h++;
			if(h == 24){
				h = 0;
			}
		}
	}
	
	printf("%02d %02d %02d", h, m , s);
	
	return 0;
}

