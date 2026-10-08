#include <stdio.h>

int main()
{
	int numLength = 1, revernumLength = 1, reverseNum = 0, saveNum = 0, num = 0;
	scanf("%d", &num);
	
	saveNum = (int) num;
	
	while( (float)(num / numLength) > 10)
	{
		numLength = numLength * 10;
	}
	
	while(num > 0)
	{
		reverseNum += (int)(num/numLength) * revernumLength;
		num -= (int)(num / numLength) * numLength;
		numLength /= 10;
		revernumLength *= 10;
	}
	
	if(saveNum == reverseNum)
	{
		printf("1");
	}
	else
	{
		printf("0");
	}
	
	return 0;
}

