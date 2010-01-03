#include <stdio.h>
#include <ctype.h>

void sort(int a[], int n)
{
	int i, j, t;

	for (i = 1; i < n; i++) {
		for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
			a[j + 1] = a[j];
		a[j + 1] = t;
	}
}

int get(int a[])
{
	int c, n;

	for (n = 0;;) {
		if (scanf("%d", &a[n]) != 1) break;
		n++;
		while ((c = getchar()) != EOF && c != '\n' && !isdigit(c) && c != '-' && c != '+');
		if (c == EOF || c == '\n')
			break;
		ungetc(c, stdin);
	}

	return n;
}

int main()
{
	static int b[128], w[128], n, m, h, s;
	int x, y, z, r;

	while (scanf("%d", &h) == 1 && h > 0) {
		n = get(b);
		m = get(w);

		sort(b, n);
		sort(w, m);

		for (x = n - 1; x >= 0; x--) {
			if ((s = b[x]) >= h) continue;

			for (y = m - 1; y >= 0; y--) {
				if ((s + w[y]) >= h) continue;
				s += w[y];

				for (z = n - 1; z >= 0; z--) {
					if ((s + b[z]) >= h || x == z) continue;
					s += b[z];

					for (r = m - 1; r >= 0; r--) {
						if ((s + w[r]) != h || y == r)
							continue;
						goto found;
					}

					s -= b[z];
				}

				s -= w[y];
			}
		}

		printf("no solution\n");
		continue;

found:		printf("%d %d %d %d\n", b[x], w[y], b[z], w[r]);
	}

	return 0;
}
