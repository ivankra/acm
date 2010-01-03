#include <stdio.h>
#include <string.h>

void xrot(int a[])
{
	int t = a[0];
	a[0] = a[1];
	a[1] = a[3];
	a[3] = a[5];
	a[5] = t;
}

void yrot(int a[])
{
	int t = a[0];
	a[0] = a[4];
	a[4] = a[3];
	a[3] = a[2];
	a[2] = t;
}

void zrot(int a[])
{
	int t = a[1];
	a[1] = a[2];
	a[2] = a[5];
	a[5] = a[4];
	a[4] = t;
}

int get()
{
	static int a[6];
	int i, r, t, x, y, z;

	for (i = 0; i < 6; i++) {
		scanf("%d", &a[i]);
		a[i]--;
	}

	for (r = 0x3FFFFFFF, x = 0; x < 4; x++, xrot(a)) {
		for (y = 0; y < 4; y++, yrot(a)) {
			for (z = 0; z < 4; z++, zrot(a)) {
				for (t = 0, i = 0; i < 6; i++)
					t = t * 6 + a[i];
				if (t < r) r = t;
			}
		}
	}

	return r;
}

int main()
{
	static int a[65536];
	int i, n;

	while (scanf("%d", &n) == 1 && n > 0) {
		memset(a, 0, sizeof(a));
		for (i = 0; i < n; i++)
			a[get()] = 1;

		for (n = 0, i = 0; i < 65536; i++)
			n += a[i];

		printf("%d\n", n);
	}

	return 0;
}
