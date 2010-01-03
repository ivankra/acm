#include <stdio.h>
#include <string.h>

int main()
{
	static unsigned long long w[512][512];
	static char s[1024];
	int a, b, c, i, j, k;
	unsigned long long r;

	memset(w, 0, sizeof(w));

	w[0][0] = 1;
	for (k = 1; k <= 300; k++)
		for (i = 1; i <= 300; i++)
			for (j = k; j <= 300; j++)
				w[i][j] += w[i - 1][j - k];

	while (gets(s)) {
		switch (sscanf(s, "%d %d %d", &a, &b, &c)) {
			case 1:
				for (i = 0, r = 0; i <= 300; i++)
					r += w[i][a];
				printf("%llu\n", r);
				break;
			case 2:
				for (i = 0, r = 0; i <= 300 && i <= b; i++)
					r += w[i][a];
				printf("%llu\n", r);
				break;
			case 3:
				for (i = b, r = 0; i <= 300 && i <= c; i++)
					r += w[i][a];
				printf("%llu\n", r);
				break;
		}
	}

	return 0;
}
