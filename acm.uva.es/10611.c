#include <stdio.h>

int main()
{
	static int d[65536], n, qn, q;
	register int i, a, b;

	scanf("%d %d", &n, &d[0]);
	for (i = 1; i < n;) {
		scanf("%d", &d[i]);

		if (d[i] == d[i - 1])
			n--;
		else 
			i++;
	}

	scanf("%d", &qn);

	while (qn-- > 0) {
		scanf("%d", &q);

		for (a = 0, b = n - 1; a < b;) {
			i = (a + b) >> 1;

			if (d[i] < q)
				a = i + 1;
			else
				b = i - 1;
		}

		b = a + 3;
		a -= 3;
		if (a < 0) a = 0;
		if (b > n) b = n - 1;

		while ((a + 1) < n && d[a + 1] < q) a++;

		while (b > 0 && d[b - 1] > q) b--;

		if (a < n && d[a] < q) printf("%d ", d[a]); else printf("X ");
		if (b >= 0 && d[b] > q) printf("%d\n",d[b]); else printf("X\n");
	}

	return 0;
}
