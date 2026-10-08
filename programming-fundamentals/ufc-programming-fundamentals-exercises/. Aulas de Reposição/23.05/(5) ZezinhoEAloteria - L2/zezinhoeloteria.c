
#include <stdio.h>

int fatorial(int value)
{
	int ret = 1;
	
	while(value > 0)
	{
		
		ret = ret * value;
		value--;
	}
	return ret;
}

int combinacao(int n, int k)
{
	return (fatorial(n)/ (fatorial(k) * fatorial( (n - k) ) ))	;
}

int main(int argc, char **argv)
{
	/*
	 * linha1: valor n
	 * linha2: valor k
	 * 
	 * */
	
	int n = 0, k = 0;
	
	scanf("%d\n%d", &n, &k);
	
	printf("%d", combinacao(n, k));
	
	return 0;
}

