#include <stdio.h>

int ex[1024], ey[1024], ez[1024], dist[1024], em, n;
void add(int x, int y, int z) { ex[em]=x; ey[em]=y; ez[em]=z; em++; }

int neg()
{
	int i, s, f;

	for (i = 0; i < n; i++) dist[i] = 0x3FFFFFFF;
	dist[0] = 0;

	for (s = 0;; s++) {
		for (f = 0, i = 0; i < em; i++)
			if (dist[ey[i]] > dist[ex[i]] + ez[i])
				f++, dist[ey[i]] = dist[ex[i]] + ez[i];
		if (f == 0) return 0;
		if (s >= n) return 1;
	}
}

int main()
{
	char s[16];
	int i, m, x, y, z;

	while (scanf("%d %d", &n, &m) == 2 && n > 0) {
		n += 2;
		em = 0;
		while (m-- > 0 && scanf("%d %d %s %d", &x, &y, s, &z) == 4)
			if (s[0] == 'g' || s[0] == 'G')
				add(x+y+1, x, -z-1);
			else
				add(x, x+y+1, z-1);

		for (i = 1; i < n; i++)
			add(0, i, 0);

		printf(neg() ? "successful conspiracy\n" : "lamentable kingdom\n");
	}

	return 0;
}
