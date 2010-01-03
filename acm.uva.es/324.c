#include <stdio.h>
#include <string.h>

int f[512][16];

void make()
{
	static int a[1024], n;
	int i, j, k;

	memset(f, 0, sizeof(f));

	for (a[0] = 1, n = 1, k = 1; k <= 370;) {
		for (i = 0; i < n; i++)
			f[k][a[i]]++;

		for (k++, i = j = 0; i < n; i++, j /= 10)
			a[i] = (j += a[i] * k) % 10;

		for (; j != 0; j /= 10)
			a[n++] = j % 10;
	}
}

int main()
{
	int n;

	for (make(); scanf("%d", &n) == 1 && n > 0;) {
		printf("%d! --\n", n);

		printf("   (0)%5d    (1)%5d    (2)%5d    (3)%5d    (4)%5d\n",
		       f[n][0], f[n][1], f[n][2], f[n][3], f[n][4]);

		printf("   (5)%5d    (6)%5d    (7)%5d    (8)%5d    (9)%5d\n",
		       f[n][5], f[n][6], f[n][7], f[n][8], f[n][9]);
	}

	return 0;
}
