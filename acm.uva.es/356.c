#include <stdio.h>
#include <string.h>

int in(int x, int y, int r)
{
	return ((x * x + y * y) <= (r * r)) ? 1 : 0;
}

void count(int n, int z[2])
{
	int x, y, k, r;

	r = 2 * n - 1;

	z[0] = z[1] = 0;

	for (x = 2; x <= (r + 2); x += 2) {
		for (y = 2; y <= (r + 2); y += 2) {
			k = in(x, y, r) + in(x - 2, y, r)
				+ in(x, y - 2, r) + in(x - 2, y - 2, r);

			if (1 <= k && k <= 3)
				z[0]++;

			if (k == 4)
				z[1]++;
		}
	}

	z[0] *= 4;
	z[1] *= 4;
}

int main()
{
	int got[256], r[256][2], n, t;

	memset(got, 0, sizeof(got));
	for (t = 0; scanf("%d", &n) == 1; t++) {
		if (got[n] == 0) {
			count(n, r[n]);
			got[n]++;
		}

		printf(
			"%sIn the case n = %d, "
			"%d cells contain segments of the circle.\n"
			"There are %d cells completely contained in the circle.\n",
			t ? "\n" : "", n, r[n][0], r[n][1]
		);
	}

	return 0;
}
