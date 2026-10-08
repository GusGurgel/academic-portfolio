
#include <stdio.h>

int main(int argc, char **argv)
{
	
	int digit = 0, celNum = 0; 
	int whileCoutn = 9, repetCount = 0; 
	int numberLength = 10000000;
	
	
	scanf("%d\n%d", &digit, &celNum);
	
	while(whileCoutn > 1)
	{
		whileCoutn--;
		if( ((int)(celNum/numberLength))  == digit)
		{
			repetCount++;
		}
		celNum -= ((int)(celNum/numberLength)) * numberLength;
		numberLength = numberLength/10;
	}
	printf("%d", repetCount);
	return 0;
}

