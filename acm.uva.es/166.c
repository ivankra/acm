#include <stdio.h>

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int main()
{
	int coin[] = { 1, 2, 4, 10, 20, 40 };
	int full[1024], tab[1024], a[8], i, k, m, z;

	full[0] = 0;
	for (k = 1; k < 1024; k++) {
		full[k] = full[k - 1] + 1;
		for (i = 1; i < 6 && k >= coin[i]; i++)
			full[k] = min(full[k], full[k - coin[i]] + 1);
	}

	for (;;) {
		for (i = m = 0; i < 6; i++) {
			scanf("%d", &a[i]);
			m += (a[i] = min(a[i], 250)) * coin[i];
		}
		m = min(m, 1024);

		if (m == 0)
			break;

		scanf("%d.%d", &a[6], &a[7]);
		z = a[6] * 20 + a[7] / 5;

		tab[0] = 0;
		for (i = 1; i <= m; i++)
			tab[i] = 0x3FFFFFFF;

		for (k = 0; k < 6; k++)
			while (a[k]-- > 0)
				for (i = m; i >= coin[k]; i--)
					tab[i] = min(tab[i], tab[i - coin[k]] + 1);

		for (k = tab[z], i = z; i <= m; i++)
			k = min(k, tab[i] + full[i - z]);

		printf("%3d\n", k);
	}

	return 0;
}
