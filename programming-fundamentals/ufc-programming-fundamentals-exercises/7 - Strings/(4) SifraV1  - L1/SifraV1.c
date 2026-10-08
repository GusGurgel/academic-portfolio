#include <stdio.h>

int main()
{
	//Se c > 'z' então c % z
	//Se c < 'a' então c = ('a' - c) - 'z'
	
	char c;
	int offsetChar = 0;
	
	scanf("%c\n%d", &c, &offsetChar);
	
	c += offsetChar;
	
	if(c > 'z')
	{
		c = ( (c % 'z') + 'a') - 1;
	}
	else if(c < 'a')
	{
		c = ('z' - ('a' - c)) + 1;
	}
	
	printf("%c", c);
	
	return 0;
}


