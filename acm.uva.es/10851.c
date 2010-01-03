#include <stdio.h>
#include <string.h>

char image[16][1024];

void decode()
{
	int i, j, c, m;

	m = strlen(image[0]) - 2;

	for (j = 1; j <= m; j++) {
		for (i = 8, c = 0; i >= 1; i--)
			if (image[i][j] == '\\')
				c = (c << 1) | 1;
			else
				c <<= 1;
		putchar(c);
	}

	printf("\n");
}

int main()
{
	int i, t;

	for (scanf("%d", &t); t-- > 0;) {
		for (i = 0; i < 10; i++)
			scanf(" %[/\\]", image[i]);

		decode();
	}

	return 0;
}
