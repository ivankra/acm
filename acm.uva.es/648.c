#include <stdio.h>
#include <stdlib.h>

int a[32], n;
int r[4], rs, rh, rm, rc;

void check(int b[], int m)
{
	int i, h, s;

	for (i = 0, s = 0; i < m; i++)
		if (i == 0 || b[i - 1] != b[i]) s++;

	h = a[b[m - 1]];

	if (rc > 0 && rs == s && rm == m && rh == h) {
		rc++;
		return;
	}

	if (rc != 0) {
		if (!(s > rs || (s == rs && (m < rm || (m == rm && h > rh)))))
			return;
		rc = 0;
	}

	rc = 1; rs = s; rm = m; rh = h;
	for (i = 0; i < m; i++) r[i] = b[i];
}

void solve(int s)
{
	int b[4], p[4], i;

	rc = 0;

	for (b[0] = 0; b[0] < n; b[0]++) {
		p[0] = a[b[0]];
		if (p[0] > s) break;
		if (p[0] == s) check(b, 1);

		for (b[1] = b[0]; b[1] < n; b[1]++) {
			p[1] = p[0] + a[b[1]];
			if (p[1] > s) break;
			if (p[1] == s) check(b, 2);

			for (b[2] = b[1]; b[2] < n; b[2]++) {
				p[2] = p[1] + a[b[2]];
				if (p[2] > s) break;
				if (p[2] == s) check(b, 3);

				for (b[3] = b[2]; b[3] < n; b[3]++)
					if ((p[2] + a[b[3]]) == s) check(b, 4);
			}
		}
	}

	if (rc == 0) {
		printf("%d ---- none\n", s);
	} else if (rc > 1) {
		printf("%d (%d): tie\n", s, rs);
	} else {
		printf("%d (%d):", s, rs);
		for (i = 0; i < rm; i++) printf(" %d", a[r[i]]);
		printf("\n");
	}
}

int cmp(const void *p, const void *q)
{
	return *(int *)p - *(int *)q;
}

int main()
{
	int s;

	for (;;) {
		for (n = 0;; n++) {
			if (scanf("%d", &a[n]) != 1) return 0;
			if (a[n] == 0) break;
		}

		qsort(a, n, sizeof(a[0]), &cmp);

		while (scanf("%d", &s) == 1 && s != 0)
			solve(s);
	}

	return 0;
}
