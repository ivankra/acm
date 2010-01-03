/*
ID: infnty1
TASK: tselect
LANG: C++
*/
/* greedy */
#include <stdio.h>

int main()
{
	int m[512], p[512], n, x, y, in[512];

	freopen("tselect.in", "r", stdin);
	freopen("tselect.out", "w", stdout);

	scanf("%d %d", &n, &x);
	y = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &m[i], &p[i]);
		in[i] = (m[i] >= 0) ? 1 : 0;
		y += in[i] * m[i];
	}

	if (y < x) { printf("-1\n"); return 0; }

	for (;;) {
		int best = -1, cost = 1<<30;

		for (int i = 1; i <= n; i++) {
			if (p[i] == 0 || (in[i] && in[p[i]])) continue;
			int c = (in[i] ? 0 : -m[i]) + (in[p[i]] ? 0 : -m[p[i]]);
			if (c < cost) { cost = c; best = i; }
		}
		if (best < 0 || y-cost < x) break;

		y -= cost;
		in[best] = in[p[best]] = 1;
	}

	y = 0;
	for (int i = 1; i <= n; i++)
		if (in[i] && p[i] != 0 && in[p[i]]) y++;
	printf("%d\n", y);

	return 0;
}
