#include <stdio.h>

int main(int argc, char **argv)
{
	int n = 1, i = 0;
	
	scanf("%d", &i);
	
	while(i > 1)
	{
		n = ( n + (n + 1) );
		i--;
	}
	
	printf("%d", n);

	
	return 0;
}
