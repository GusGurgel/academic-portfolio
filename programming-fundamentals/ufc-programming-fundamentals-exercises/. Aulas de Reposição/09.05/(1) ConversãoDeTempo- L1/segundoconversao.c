#include <stdio.h>

int main(int argc, char **argv)
{
	int segundos; 
	
	scanf("%d", &segundos);
	
	printf("%d\n", (segundos/3600));
	printf("%d\n", (segundos%3600)/60);
	printf("%d\n", (segundos%3600)%60);
	
	return 0;
}
