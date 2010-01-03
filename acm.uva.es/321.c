#include <stdio.h>
#include <string.h>

int adj[16][16], sw[16][16], n;

void solve()
{
	static int dist[16384], pred[16384], action[16384], queue[16384];
	int head, tail, i, r, s, t;

	memset(dist, 0, sizeof(dist));

	s = ((n - 1) << 10) | (1 << (n - 1));

	head = tail = 0;
	queue[tail++] = s;
	dist[s] = 1;

	while (head < tail) {
		s = queue[head++];
		r = s >> 10;

		for (i = n - 1; i >= 0; i--) {
			if (i == r || sw[r][i] == 0)
				continue;

			t = s ^ (1 << i);

			if (dist[t] == 0) {
				dist[t] = dist[s] + 1;
				pred[t] = s;
				action[t] = i + 1;
				if (s & (1 << i)) action[t] += 0x10000;
				queue[tail++] = t;
			}
		}

		for (i = 0; i < n; i++) {
			if (adj[r][i] == 0 || ((s >> i) & 1) == 0)
				continue;

			t = (s & 1023) | (i << 10);
			if (dist[t] == 0) {
				dist[t] = dist[s] + 1;
				pred[t] = s;
				action[t] = -(r + 1);
				queue[tail++] = t;
			}
		}
	}

	s = ((n - 1) << 10) | (1 << (n - 1));
	t = 1;

	if (dist[t] == 0) {
		printf("The problem cannot be solved.\n");
		return;
	}

	printf("The problem can be solved in %d steps:\n", dist[t] - 1);

	for (; t != s; t = pred[t]) {
		if (action[t] > 0)
			printf("- Switch %s light in room %d.\n",
				(action[t] & 0x10000) ? "on" : "off",
				action[t] & 0xFFFF);
		else
			printf("- Move to room %d.\n", -action[t]);
	}
}

int main()
{
	int d, s, t, x, y;

	for (t = 1; scanf("%d %d %d", &n, &d, &s) == 3; t++) {
		if (n == 0 && d == 0 && s == 0) break;

		memset(adj, 0, sizeof(adj));
		memset(sw, 0, sizeof(sw));

		while (d-- > 0 && scanf("%d %d", &x, &y) == 2)
			adj[x - 1][y - 1] = adj[y - 1][x - 1] = 1;

		while (s-- > 0 && scanf("%d %d", &x, &y) == 2)
			sw[x - 1][y - 1] = 1;

		printf("Villa #%d\n", t);
		if (n <= 1) {
			printf("The problem can be solved in 0 steps:\n");
		} else {
			solve();
		}
		printf("\n");
	}

	return 0;
}
