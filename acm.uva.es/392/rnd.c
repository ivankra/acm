#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i, j;

	srand(time(NULL));

	for (i = 0; i < 10000; i++)
		for (j = 0; j < 9; j++)
			printf(" %d",
			       (((rand()&0xFF)<0x90) ? 0 : (rand() % 1000))
			       * (((rand() & 0xFF) < 0x80) ? 1 : -1)
				);
}
