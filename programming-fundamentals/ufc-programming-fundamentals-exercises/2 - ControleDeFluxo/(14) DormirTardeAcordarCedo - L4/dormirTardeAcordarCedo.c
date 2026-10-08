#include <stdio.h>

int main(int argc, char **argv)
{
	
	int Hd, Md, Sd;
	int Ha, Ma, Sa;
	int Hr = 0, Mr = 0, Sr = 0;
	int mesmoDia = 0;

	scanf("%d %d %d", &Hd, &Md, &Sd);
	scanf("%d %d %d", &Ha, &Ma, &Sa);

	if(Hd == Ha)
	{
		if(Md == Ma)
		{
			if(Sd > Sa)
			{
				mesmoDia = 0;
			}
			else
			{
				mesmoDia = 1;
			}
		}
		else
		{
			if(Md > Ma)
			{
				mesmoDia = 0;
			}
			else
			{
				mesmoDia = 1;
			}
		}
	}
	else
	{
		if(Hd > Ha)
		{
			mesmoDia = 0;
		}
		else
		{
			mesmoDia = 1;
		}
	}
	
	if(!mesmoDia)
	{
		Ha += 24;
	}
	
	Hr = Ha - Hd;
	Mr = Ma - Md;
	Sr = Sa - Sd;
		
	if(Sr < 0)
		{
		Mr--;
		Sr += 60;
	}
	if(Mr < 0)
	{
		Hr--;
		Mr += 60;
	}
	
	printf("%d %d %d", Hr, Mr, Sr);
	
	return 0;
}
