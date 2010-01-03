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

int main()
{
	int a[6] = { 0, 1, 2, 3, 4, 5 };
	int x, y, z, i;

	for (x = 0; x < 4; x++, xrot(a))
		for (y = 0; y < 4; y++, yrot(a))
			for (z = 0; z < 4; z++, zrot(a)) {
				for (i = 0; i < 6; i++)
					printf(i ? ", %d" : "\t{ %d", a[i]);
				printf(" },\n");
			}

	return 0;
}
