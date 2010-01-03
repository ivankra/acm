#include <stdio.h>
#include <memory.h>

static unsigned char lookup[1048576];
static int cubes[256];

#define ISPERFECT(n) ((lookup[(n) >> 3] >> ((n) & 7)) & 1)

static int root(int x)
{
	int a, b, c;

	for (a = 0, b = 200; a < b;) {
		c = (a + b) >> 1;

		if (cubes[c] < x)
			a = c + 1;
		else if (cubes[c] > x)
			b = c - 1;
		else
			return c;
	}

	return a;
}

int main()
{
	static int a, b, b3, c, c3, d, d3;
	static int r[256][4], n;
	register int i;

	memset(lookup, '\0', sizeof(lookup));
	for (i = 0; i <= 200; i++) {
		d = i * i * i;
		cubes[i] = d;
		lookup[d >> 3] |= (1 << (d & 7));
	}

	n = 0;
	for (b = 2; b <= 200; b++) {
		b3 = cubes[b];
		for (c = b; c <= 200; c++) {
			c3 = cubes[c];
			for (d = c; d <= 200; d++) {
				i = cubes[d] + c3 + b3;

				if (i > 8000000)
					break;

				if (ISPERFECT(i)) {
					r[n][0] = i;
					r[n][1] = b;
					r[n][2] = c;
					r[n][3] = d;
					n++;
				}
			}
		}
	}

#if 0
	for (i = 0; i < n; i++) {
		printf("Cube = %d, Triple = {%d,%d,%d}\n",
			root(r[i][0]), r[i][1], r[i][2], r[i][3]);
	}
#endif

	for (i = 0; i < n; i++) {
		printf("%3d,%3d,%3d,%3d,\n",
			root(r[i][0]), r[i][1], r[i][2], r[i][3]);
	}

	return 0;
}
