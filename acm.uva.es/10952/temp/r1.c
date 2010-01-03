#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int i, j, t, w, h;

	srand(time(NULL));

	printf("%d\n\n", t=1000);
	while (t-- > 0) {
		printf("%d %d\n", w=3, h=3);
		for (i = 0; i < h; i++) {
			for (j = 0; j < w; j++)
				putchar(".OX"[rand() % 3]);
			putchar(' ');
			for (j = 0; j < w; j++)
				putchar(".OX"[rand() % 3]);
			putchar('\n');
		}
		printf("\n");
	}

	return 0;
}
