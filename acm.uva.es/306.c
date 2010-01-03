#include <stdio.h>
#include <string.h>

void apply(int a[], int p[], int n)
{
	static int t[1024];
	int i;

	for (i = 0; i < n; i++)
		t[i] = p[a[i]];

	for (i = 0; i < n; i++)
		a[i] = t[i];
}

void power(int z[], int a[], int n, int k)
{
	static int m[1024];
	int i;

	for (i = 0; i < n; i++)
		m[i] = a[i];

	for (i = 0; i < n; i++)
		z[i] = i;

	for (; k > 0; k >>= 1) {
		if (k & 1)
			apply(z, m, n);

		apply(m, m, n);
	}
}

int main()
{
	static char s1[4096], s2[4096];
	static int a[1024], p[1024];
	int i, j, k, n;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < n && scanf("%d", &a[i]) == 1; i++)
			a[i]--;

		while (gets(s1)) {
			if (sscanf(s1, "%d", &k) != 1)
				continue;

			if (k == 0)
				break;

			for (i = 0; s1[i] && s1[i] != ' '; i++);

			if (s1[i] == ' ')
				i++;

			for (j = 0; s1[i];)
				s2[j++] = s1[i++];

			while (j < n)
				s2[j++] = ' ';

			power(p, a, n, k);

			for (i = 0; i < n; i++)
				s1[p[i]] = s2[i];
			s1[n] = '\0';

			printf("%s\n", s1);
		}

		printf("\n");
	}

	return 0;
}
