#include <stdio.h>
#include <string.h>

long long prod[32][32];
char buf[1024], s1[256], s2[256];

void ins(char c, int p)
{
	int i, m;

	m = strlen(s2);
	if (p > m) p = m;

	for (i = m; i >= p; i--)
		s2[i + 1] = s2[i];
	s2[p] = c;
}

int main()
{
	int i, j, k, n, t;
	long long s, z;

	for (i = 0; i < 32; i++) {
		for (j = 0; j < 32; j++) {
			prod[i][j] = 1;
			for (k = i; k <= j; k++) {
				prod[i][j] = prod[i][j] * (long long)k;
				if (prod[i][j] > 0x7FFFFFFF) break;
			}
		}
	}

	while (gets(buf) && sscanf(buf, "%d", &t) != 1);

	while (t-- > 0) {
		memset(s1, 0, sizeof(s1));
		gets(buf);
		sscanf(buf, " %[A-Z]", s1);
		n = strlen(s1);

		gets(buf);
		sscanf(buf, "%lld", &z);

		memset(s2, 0, sizeof(s2));
		for (k = 1; k <= n; k++) {
			for (s = 0, i = 1; i <= n; i++) {
				if ((s + prod[k + 1][n]) >= z) break;
				s += prod[k + 1][n];
			}

			ins(s1[k - 1], i - 1);
			z -= s;
		}

		printf("%s\n", s2);
	}

	return 0;
}
