#include <stdio.h>

int tab[65536];

int a[48] = {
	1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384,
	32768, 49152, 3072, 192, 12, 12288, 768, 48, 3, 34816, 17408, 8704,
	4352, 136, 68, 34, 17, 57344, 3584, 224, 14, 28672, 1792, 112, 7,
	34944, 17472, 8736, 4368, 2184, 1092, 546, 273
};

int f(int x)
{
	int i;

	if (tab[x] >= 0) return tab[x];

	for (i = 0; i < 48; i++)
		if ((x & a[i]) == 0 && f(x | a[i]) == 0) return (tab[x] = 1);

	return (tab[x] = 0);
}

int main()
{
	int i, j, k, t;

	for (i = 0; i < 65536; i++) tab[i] = -1;
	tab[0xFFFF] = 1;

	for (scanf("%d", &t); t-- > 0;) {
		for (i = j = 0; i < 16 && (k = getchar()) != EOF;)
			if (k == '.')
				i++, j <<= 1;
			else if (k == 'X' || k == 'x')
				i++, j = (j << 1) | 1;
		if (i < 16) break;

		printf(f(j) ? "WINNING\n" : "LOSING\n");
	}

	return 0;
}
