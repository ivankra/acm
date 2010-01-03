#include <stdio.h>
#include <string.h>

int get()
{
	static int h, m;
	scanf("%d:%d", &h, &m);
	return ((h - 10) * 60 + m);
}

int main()
{
	static int a[512], d, n, rs, rl;
	int i, j;

	for (d = 1; scanf("%d", &n) == 1; d++) {
		memset(a, 0, sizeof(a));

		while (n-- > 0) {
			i = get();
			j = get();

			scanf("%*[^\n]");

			while (i < j)
				a[i++] = 1;
		}

		for (i = 0, j = 0, rs = 0, rl = -1; i < 480; i++) {
			if (a[i] == 0) {
				j++;
			} else {
				if (j > rl) {
					rs = i - j;
					rl = j;
				}
				j = 0;
			}
		}

		if (j > rl) {
			rs = i - j;
			rl = j;
		}

		printf("Day #%d: the longest nap starts at %d:%.2d and will last for ",
			d, (rs / 60) + 10, rs % 60);

		if (rl < 60)
			printf("%d minutes.\n", rl);
		else
			printf("%d hours and %d minutes.\n", rl / 60, rl % 60);
	}

	return 0;
}
