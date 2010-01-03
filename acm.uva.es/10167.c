#include <stdio.h>

int px[128], py[128], n;

int vline()
{
	int i, k;

	for (i = k = 0; i < n; i++) {
		if (px[i] == 0)
			return 0;
		else
			k += (px[i] < 0) ? 1 : -1;
	}

	if (k != 0)
		return 0;

	printf("1 0\n");
	return 1;
}

int hline()
{
	int i, k;

	for (i = k = 0; i < n; i++) {
		if (py[i] == 0)
			return 0;
		else
			k += (py[i] < 0) ? 1 : -1;
	}

	if (k != 0)
		return 0;

	printf("0 1\n");
	return 1;
}

int check(int a, int b)
{
	int i, k, det;

	for (i = k = 0; i < n; i++) {
		det = a * px[i] + b * py[i];
		if (det == 0)
			return 0;
		else
			k += (det > 0) ? 1 : -1;
	}

	return (k == 0);
}

void generic()
{
	int a, b;

	for (b = 1; b <= 500; b++) {
		for (a = -500; a <= 500; a++) {
			if (a == 0 || ((a | b) & 1) == 0) continue;

			if (check(a, b)) {
				printf("%d %d\n", a, b);
				return;
			}
		}
	}
}

int main()
{
	int i;

	while (scanf("%d", &n) == 1 && n > 0) {
		n *= 2;

		for (i = 0; i < n; i++)
			scanf("%d %d", &px[i], &py[i]);

		if (hline()) continue;
		if (vline()) continue;
		generic();
	}

	return 0;
}
