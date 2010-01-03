#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int main()
{
	double f, d;
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

			d = d * (double)x + f;
			f = f * (double)x + (double)a;

			i++;
		}

		if (d > 0) {
			if ((ceil(d) - d) < (d - floor(d)))
				x = (int)ceil(d);
			else
				x = (int)floor(d);
		} else {
			d = -d;
			if ((ceil(d) - d) < (d - floor(d)))
				x = -(int)ceil(d);
			else
				x = -(int)floor(d);
		}

		printf("%d\n", x);
	}

	return 0;
}
