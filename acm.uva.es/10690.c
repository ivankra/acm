#include <stdio.h>
#include <string.h>

#define SHIFT 5120

int a[1024], n, m, s, r1, r2;
int qx[131072], qk[131072], qn;
char got[128][2 * SHIFT];

int main()
{
	int i, j, k;

	while (scanf("%d %d", &n, &m) == 2) {
		if (n < m)
			k = n, n = m, m = k;
		n += m;

		for (i = s = 0; i < n; i++) {
			scanf("%d", &a[i]);
			s += a[i];
		}

		memset(got, 0, sizeof(got));
		got[0][SHIFT] = 1;

		qx[0] = SHIFT;
		qk[0] = 0;
		qn = 1;

		for (i = 0; i < n; i++) {
			for (j = qn - 1; j >= 0; j--) {
				if (qk[j] >= m) continue;
				if (got[qk[j] + 1][qx[j] + a[i]]) continue;

				qk[qn] = qk[j] + 1;
				qx[qn] = qx[j] + a[i];
				got[qk[qn]][qx[qn]] = 1;
				qn++;
			}
		}

		r1 = -0x3FFFFFFF;
		r2 = 0x3FFFFFFF;
		for (k = 0; k < qn; k++) {
			if (qk[k] != m)
				continue;

			i = qx[k] - SHIFT;

			if ((i * (s - i)) > r1) r1 = i * (s - i);
			if ((i * (s - i)) < r2) r2 = i * (s - i);
		}

		printf("%d %d\n", r1, r2);
	}
}
