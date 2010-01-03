#include <stdio.h>

int main()
{
	static int cyc[128], r[128], st[128], m, n, t;
	int i;

	for (;;) {
		for (n = 0; scanf("%d", &cyc[n]) == 1 && cyc[n] > 0; n++);

		if (n == 0)
			break;

		for (i = 0; i < n; i++) {
			st[i] = 0;
			r[i] = cyc[i] - 5;
		}

		for (t = 0; t <= 18000;) {
			for (m = r[0], i = 1; i < n; i++)
				if (r[i] < m) m = r[i];

			for (t += m, i = 0; i < n; i++) {
				if ((r[i] -= m) > 0)
					continue;

				if (st[i] == 0) {
					st[i] = 1;
					r[i] = 5;
				} else if (st[i] == 1) {
					st[i] = 2;
					r[i] = cyc[i];
				} else {
					st[i] = 0;
					r[i] = cyc[i] - 5;
				}
			}

			for (i = 0; i < n; i++)
				if (st[i] != 0) break;

			if (i >= n)
				break;
		}

		if (t > 18000)
			printf ("Signals fail to synchronise in 5 hours\n");
		else
			printf("%.2d:%.2d:%.2d\n",
			       t / 3600, (t % 3600) / 60, t % 60);
	}

	return 0;
}
