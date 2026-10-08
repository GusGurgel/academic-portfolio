#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	char name[100];
	int sum = 0;
	
	scanf("%s", name);
	
	for(int i = 0; i < strlen(name); i++)
	{
		sum += name[i];
	}
	
	printf("%d", (sum % 50) );
	
	return 0;
}


