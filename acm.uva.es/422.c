#include <stdio.h>
#include <memory.h>

static char m[128][128];
static int n, found;

static struct {
	int dy, dx;
} tr[] = {
	{ 0, 1 },
	{ 0, -1 },

	{ 1, 0 },

	{ 1, 1 },
	{ 1, -1 },

	{ -1, 1 },
	{ -1, -1 }
};

int main()
{
	static char w[128];
	register int i, x, y, x2=0, y2=0, len, t;

	memset(m, 0, sizeof(m));

	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf(" %127[A-Za-z]", m[i]);

	while (scanf(" %127[A-Za-z0]", w) == 1 && w[0] != '0' && w[0] != 0) {
		for (len = 0; w[len]; len++);

		found = 0;
		for (x = 0, y = 0; y < n; (++x >= n) ? (y++, x = 0) : 0) {
			if (m[y][x] != w[0])
				continue;

			for (t = 0; t < 7; t++) {
				for (x2 = x, y2 = y, i = 0;;) {
					if (m[y2][x2] != w[i])
						break;

					if (++i >= len)
						break;

					x2 += tr[t].dx;
					y2 += tr[t].dy;

					if (x2 < 0 || x2 >= n ||
					    y2 < 0 || y2 >= n)
						break;
				}

				if (i == len) {
					found = 1;
					break;
				}
			}

			if (found)
				break;
		}

		if (found)
			printf("%d,%d %d,%d\n", 1+y, 1+x, 1+y2, 1+x2);
		else
			printf("Not found\n");
	}

	return 0;
}
