#include <stdio.h>

int main(int argc, char **argv)
{
	int jog1, jog2, jog3;
	scanf("%d\n%d\n%d", &jog1, &jog2, &jog3);
	
	//printf("%d\n%d\n%d\n", jog1, jog2, jog3);
	
	//Se não de empate
	if( !((jog1 == jog2) && (jog2 == jog3)) ){
		if( ((jog1 == jog2) && (jog3 != jog2)) ){
			printf("jog3");
		}else if( ((jog1 == jog3) && (jog2 != jog1)) ){
			printf("jog2");
		}else{
			printf("jog1");
		}
	}else{
		printf("empate");
	}
	
	return 0;
}

