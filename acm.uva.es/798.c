#include <stdio.h>
#include <string.h>

int w[16], h[16], m[16], n, width, height, count;
int a[128][128], H[128][128];

static void f(int y, int x)
{
	int i, k;

	for (;; y++, x = 0) {
		if (y >= height) {
			count++;
			return;
		}

		while (x < width && H[y][x] > 0) {
			H[y + 1][x] = H[y][x] - 1;
			x++;
		}
		if (x < width) break;
	}

	for (k = 0; k < n; k++) {
		if (m[k] < 1 || (x + w[k]) > width || (y + h[k]) > height)
			continue;

		for (i = 0; i < w[k]; i++)
			if (H[y][x + i] > 0) goto next1;

		for (i = 0; i < w[k]; i++) {
			H[y][x + i] = h[k];
			H[y + 1][x + i] = h[k] - 1;
		}

		m[k]--;
		f(y, x + w[k]);
		m[k]++;

		for (i = 0; i < w[k]; i++)
			H[y][x + i] = 0;
next1: ;
	}

	for (k = 0; k < n; k++) {
		if (m[k] < 1 || w[k] == h[k] ||
		    (x + h[k]) > width || (y + w[k]) > height)
			continue;

		for (i = 0; i < h[k]; i++)
			if (H[y][x + i] > 0) goto next2;

		for (i = 0; i < h[k]; i++) {
			H[y][x + i] = w[k];
			H[y + 1][x + i] = w[k] - 1;
		}

		m[k]--;
		f(y, x + h[k]);
		m[k]++;

		for (i = 0; i < h[k]; i++)
			H[y][x + i] = 0;
next2: ;
	}
}

int main()
{
	int i;

	while (scanf("%d %d %d", &width, &height, &n) == 3) {
		for (i = 0; i < n; i++)
			scanf("%d %d %d", &m[i], &w[i], &h[i]);

		memset(a, 0, sizeof(a));
		memset(H, 0, sizeof(H));
		count = 0;
		f(0, 0);

		printf("%d\n", count);
	}

	return 0;
}
