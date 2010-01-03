#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int n, j;
	srand(3462);
	for (int i = 0 ; i < 100; i++) {
		n = (rand() % 30) + 1;
		for (j = 0; j < n; j++) putchar((rand()%3)+'a');
		putchar('\n');
		printf("%c\n", (rand()%3)+'a');
	}
	return 0;
}
