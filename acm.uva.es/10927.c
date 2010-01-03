#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct { int x, y, z; unsigned w; } pt;

pt p[131072], inv[131072];
int n, m;

int gcd(int x, int y) { return (y == 0) ? x : gcd(y, x % y); }

int cmpyx(const void *p, const void *q)
{
	if (((pt *)p)->y != ((pt *)q)->y)
		return ((pt *)p)->y - ((pt *)q)->y;
	else
		return ((pt *)p)->x - ((pt *)q)->x;
}

int cmpxy(const void *p, const void *q)
{
	if (((pt *)p)->x != ((pt *)q)->x)
		return ((pt *)p)->x - ((pt *)q)->x;
	else
		return ((pt *)p)->y - ((pt *)q)->y;
}

int cmpwy(const void *p, const void *q)
{
	if (((pt *)p)->w != ((pt *)q)->w)
		return (((pt *)p)->w > ((pt *)q)->w) ? 1 : -1;
	else
		return ((pt *)p)->y - ((pt *)q)->y;
}

void solve_y0()
{
	int i, j, k, h;

	qsort(p, n, sizeof(p[0]), &cmpyx);

	for (k = 0; k < n && p[k].y == 0; k++);
	if (k == 0) return;

	for (i = 0; (i+1) < k && p[i+1].x < 0; i++);
	for (h = -1, j = i; j >= 0; j--)
		if (p[j].z <= h) inv[m++] = p[j]; else h = p[j].z;

	while (i < k && p[i].x <= 0) i++;
	for (h = -1; i < k; i++)
		if (p[i].z <= h) inv[m++] = p[i]; else h = p[i].z;

	for (i = k, j = 0; i < n;)
		p[j++] = p[i++];
	n = j;
}

void solve_gen()
{
	int i, h, s, t;

	for (i = 0; i < n; i++) {
		t = gcd(abs(p[i].x), p[i].y);
		p[i].w = (abs(p[i].x) / t) * 10001 + (p[i].y / t);
		if (p[i].x < 0) p[i].w |= 0x80000000;
	}
	qsort(p, n, sizeof(p[0]), &cmpwy);

	for (s = 0; s < n; s = t) {
		for (t = s + 1; t < n && p[t].w == p[s].w; t++);

		for (h = -1, i = s; i < t; i++)
			if (p[i].z <= h) inv[m++] = p[i]; else h = p[i].z;
	}
}

int main()
{
	int i, t;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		assert(0 <= n && n <= 120000);
		printf("Data set %d:\n", t);

		for (i = m = 0; i < n; i++) {
			scanf("%d %d %d", &p[i].x, &p[i].y, &p[i].z);
			assert(0 <= p[i].y && 0 <= p[i].z);
			if (p[i].x == 0 && p[i].y == 0) i--, n--;
		}

		solve_y0();

		for (i = 0; i < n; i++)
			assert(p[i].y > 0);

		solve_gen();

		if (m == 0) {
			printf("All the lights are visible.\n");
		} else {
			printf("Some lights are not visible:\n");
			qsort(inv, m, sizeof(inv[0]), &cmpxy);
			for (i = 0; i < m; i++)
				printf("x = %d, y = %d%c\n", inv[i].x, inv[i].y,
					((i+1)<m) ? ';' : '.');
		}
	}

	return 0;
}
