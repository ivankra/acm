#include <stdio.h>
#include <stdlib.h>

char line[4096], buf[512], names[16];
double val[16];
int ntests, t, digpt[256];

int main()
{
	int i, k;
	char *p;

	for (i = 0; i < 256; i++)
		digpt[i] = ((i >= '0' && i <= '9') || (i == '.'));

	scanf("%d\n", &ntests);

	for (t = 1; t <= ntests && scanf(" %[^\n]\n", line) == 1; t++) {
		for (p = line, k = 0; *p;) {
			if (*p++ != '=')
				continue;

			names[k] = p[-2] & ~0x20;

			for (i = 0; digpt[*p];)
				buf[i++] = *p++;
			buf[i] = '\0';

			val[k] = atof(buf);

			if (*p == 'm')
				p++, val[k] *= 0.001;
			else if (*p == 'k')
				p++, val[k] *= 1000.;
			else if (*p == 'M')
				p++, val[k] *= 1000000.;

			if (++k >= 2)
				break;
		}

		printf("Problem #%d\n", t);
		if (names[0] == 'P' && names[1] == 'U')
			printf("I=%.2fA\n\n", val[0] / val[1]);
		else if (names[0] == 'U' && names[1] == 'P')
			printf("I=%.2fA\n\n", val[1] / val[0]);
		else if (names[0] == 'P' && names[1] == 'I')
			printf("U=%.2fV\n\n", val[0] / val[1]);
		else if (names[1] == 'P' && names[0] == 'I')
			printf("U=%.2fV\n\n", val[1] / val[0]);
		else
			printf("P=%.2fW\n\n", val[0] * val[1]);
	}

	return 0;
}
