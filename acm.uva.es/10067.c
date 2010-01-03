#include <stdio.h>
#include <string.h>

static int get()
{
	static int a, b, c, d;
	scanf("%d %d %d %d", &a, &b, &c, &d);
	return ((a * 10 + b) * 10 + c) * 10 + d;
}

int main()
{
	static int d[10000], q[10000], a[16], n, t, goal;
	int i, j, k, m, *qh, *qt;

	for (scanf("%d", &t); t-- > 0;) {
		qh = qt = q;
		*qt++ = get();
		goal = get();

		memset(d, 0, sizeof(d));

		for (scanf("%d", &n); n-- > 0;)
			d[get()] = -1;

		if (goal == *qh) {
			printf("0\n");
			continue;
		}

		for (; qh < qt && *qh != goal; qh++) {
			for (i = 3, j = *qh; i >= 0; i--, j /= 10)
				a[i] = j % 10;

			for (i = 0; i < 4; i++) {
				m = a[i];
				for (j = -1; j <= 1; j += 2) {
					a[i] = (m + 10 + j) % 10;
					k = ((a[0] * 10 + a[1]) * 10 + a[2]) * 10 + a[3];

					if (d[k] == 0) {
						*qt++ = k;
						d[k] = d[*qh] + 1;
					}
				}
				a[i] = m;
			}
		}

		printf("%d\n", (*qh == goal) ? d[goal] : -1);
	}

	return 0;
}
