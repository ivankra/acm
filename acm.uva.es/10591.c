#include <stdio.h>

int tab[1024];

void maketab()
{
	static int a[1024];
	int i, k, n, t;

	for (n = 0; n < 1024; n++) {
		for (t = n, k = 0;;) {
			if (t == 1) {
				tab[n] = 1;
				break;
			}

			if (t < n) {
				tab[n] = tab[t];
				break;
			}

			for (i = 0; i < k; i++)
				if (a[i] == t) break;

			if (i < k) {
				tab[n] = 0;
				break;
			}

			a[k++] = t;

			i = t;
			for (t = 0; i > 0; i /= 10)
				t += (i % 10) * (i % 10);
		}
	}
}

int happy(int n)
{
	int m;

	for (m = 0; n > 0; n /= 10)
		m += (n % 10) * (n % 10);

	return tab[m];
}

int main()
{
	int i, n, t;

	maketab();

	for (scanf("%d", &t), i = 1; i <= t && scanf("%d", &n) == 1; i++)
		printf("Case #%d: %d is %s number.\n", i, n,
		       happy(n) ? "a Happy" : "an Unhappy");

	return 0;
}
