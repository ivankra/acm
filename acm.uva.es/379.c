#include <stdio.h>
#include <string.h>

int a[128], down[128], up[128], left[128], right[128];
int mx, my, mz;

void check(int x, int y, int z)
{
	if (x == 0 || y == 0 || z == 0)
		return;

	if (a[x] == 0 || a[y] == 0 || a[z] == 1)
		return;

	if (z > mz || (z == mz && x > mx)) {
		mx = x;
		my = y;
		mz = z;
	}
}

void mktab()
{
	int i;

	memset(down, 0, sizeof(down));
	for (i = 1; i <= 3; i++) down[i] = i + 3;
	for (i = 4; i <= 6; i++) down[i] = i + 5;
	for (i = 7; i <= 20; i++) down[i] = i + 7;
	for (i = 23; i <= 25; i++) down[i] = i + 5;
	for (i = 28; i <= 30; i++) down[i] = i + 3;

	memset(up, 0, sizeof(up));
	for (i = 1; i <= 33; i++)
		if (down[i] != 0) up[down[i]] = i;

	memset(left, 0, sizeof(left));
	for (i = 1; i <= 33; i++)
		left[i] = i - 1;
	left[1] = left[4] = left[7] = left[14] = left[21] = left[28] = left[31] = 0;

	memset(right, 0, sizeof(right));
	for (i = 1; i <= 33; i++)
		if (left[i] != 0) right[left[i]] = i;
}

int main()
{
	int i, x, t;

	mktab();
	printf("HI Q OUTPUT\n");

	for (scanf("%d", &t); t-- > 0;) {
		memset(a, 0, sizeof(a));

		while (scanf("%d", &x) == 1 && x > 0)
			a[x] = 1;

		for (;;) {
			for (mx = my = mz = 0, i = 1; i <= 33; i++) {
				if (a[i] == 0) continue;
				check(i, down[i], down[down[i]]);
				check(i, up[i], up[up[i]]);
				check(i, left[i], left[left[i]]);
				check(i, right[i], right[right[i]]);
			}

			if (mx == 0)
				break;

			a[mx] = 0;
			a[my] = 0;
			a[mz] = 1;
		}

		for (x = 0, i = 1; i <= 33; i++)
			x += a[i] * i;

		printf("%d\n", x);
	}

	printf("END OF OUTPUT\n");
	return 0;
}
