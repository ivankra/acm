#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int main()
{
	long long f, d;
	int a, x, c, i;

	for (;;) {
		if (scanf("%d\n", &x) < 1)
			break;

		for (i = 0, f = 0., d = 0.;;) {
			while ((c = getchar()) != EOF && !isdigit(c) && c != '\n' && c != '-');
			if (c == EOF || (c == '\n' && i > 0)) break;
			if (c == '\n') continue;

			ungetc(c, stdin);
			scanf("%d", &a);

			d = d * (long long)x + f;
			f = f * (long long)x + (long long)a;

			i++;
		}

		printf("%d\n", (int)d);
	}

	return 0;
}
