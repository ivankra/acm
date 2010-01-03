#include <stdio.h>

typedef char image[16][16];

int equal(image x, image y, int n)
{
	int i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (x[i][j] != y[i][j]) return 0;

	return 1;
}

void rot90(image x, int n)
{
	static image t;
	int i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			t[i][j] = x[n - j - 1][i];

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			x[i][j] = t[i][j];
}

void vreflect(image x, int n)
{
	static image t;
	int i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			t[i][j] = x[n - i - 1][j];

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			x[i][j] = t[i][j];
}

int main()
{
	image x, y;
	int i, j, k, n, t;

	for (t = 1; scanf("%d", &n) == 1; t++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n && (k = getchar()) != EOF;)
				if (k == '.' || k == 'X') x[i][j++] = k;

			for (j = 0; j < n && (k = getchar()) != EOF;)
				if (k == '.' || k == 'X') y[i][j++] = k;
		}

		for (i = 0; i <= 270 && !equal(x, y, n); i += 90, rot90(x, n));

		if (i == 0) {
			printf("Pattern %d was preserved.\n", t);
			continue;
		} else if (i <= 270) {
			printf("Pattern %d was rotated %d degrees.\n", t, i);
			continue;
		}

		vreflect(x, n);

		for (i = 0; i <= 270 && !equal(x, y, n); i += 90, rot90(x, n));

		if (i == 0)
			printf("Pattern %d was reflected vertically.\n", t);
		else if (i <= 270)
			printf("Pattern %d was reflected vertically and "
			       "rotated %d degrees.\n", t, i);
		else
			printf("Pattern %d was improperly transformed.\n", t);
	}

	return 0;
}
