/*
ID: infnty1
PROB: ratios
LANG: C++
*/
#include <cstdio>

void get(int x[]) { scanf("%d %d %d", &x[0], &x[1], &x[2]); }

int main()
{
	freopen("ratios.in", "r", stdin);
	freopen("ratios.out", "w", stdout);

	int a[3], b[3], c[3], g[3];
	get(g); get(a); get(b); get(c);

	for (int sum = 0; sum <= 300; sum++)
	for (int x = 0; x <= 100; x++)
	for (int y = 0; y <= 100; y++) {
		int z = sum - x - y;
		if (z < 0 || z > 100) continue;

		int r[3];
		for (int i = 0; i < 3; i++)
			r[i] = x*a[i] + y*b[i] + z*c[i];

		int t = -1;
		for (int i = 0; i < 3; i++) {
			if (g[i] == 0) {
				if (r[i] != 0) { t = -2; break; }
			} else if (t < 0) {
				if (r[i] == 0 || (r[i] % g[i]) != 0) { t = -2; break; }
				t = r[i] / g[i];
			} else if (r[i] != t * g[i]) {
				t = -2; break;
			}
		}

		if (t == -2) continue;
		if (t < 0) t = 0;

		printf("%d %d %d %d\n", x, y, z, t);
		return 0;
	}

	printf("NONE\n");
}
