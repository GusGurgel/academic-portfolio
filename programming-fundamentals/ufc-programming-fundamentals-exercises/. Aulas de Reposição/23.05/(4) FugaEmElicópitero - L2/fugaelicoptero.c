#include <stdio.h>

int main(int argc, char **argv)
{
	/*
	 * D = -1 horária Diminuindo
	 * D = 1 anti-horaria Almentado
	 * 
	 * */
	 
	int H = 0, P = 0, F = 0, D = 0;
	
	scanf("%d %d %d %d", &H, &P, &F, &D);
	
	//antiHoraria
	if(D > 0)
	{
		if(F > H && F > P)
		{
			F = -1;
			while(F < 16)
			{
				F++;
				if(F == P)
				{
					printf("N\n");
					F = 15;
				}
				else if(F == H)
				{
					printf("S\n");
					F = 15;
				}
			}
		}
		else{
		while(F < 16)
		{
				F++;
				if(F == P)
				{
					printf("N\n");
					F = 15;
				}
				else if(F == H)
				{
					printf("S\n");
					F = 15;
				}
			}
		}
	}
	//Horaria
	else
	{
		if(F < H && F < P)
		{
			F = 15;
			while(F > 0)
	    	{
			    F--;
			    if(F == P)
			    {
			    	printf("S\n");
				F = 0;
			    }
			    else if(F == H)
			    {   
				    printf("N\n");
			    	F = 0;
		    	}
		}
		}
		else
		{
		    while(F > 0)
	    	{
			    F--;
		    	if(F == P)
		    	{
		    		printf("N\n");
		    		F = 0;
	    		}
	    		else if(F == H)
	    		{
		    		printf("S\n");
		    		F = 0;
	    		}
	    	}
		    
		}

	}
	 
	return 0;
}

