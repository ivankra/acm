#include <stdio.h>
#include <string.h>

char goal[65536], str[128][128];
int n, total, len[128];

int solve()
{
	static int dist[65536], queue[65536];
	int i, m, *head, *tail;

	memset(dist, 0, sizeof(dist));
	dist[0] = 1;

	head = tail = queue;
	*tail++ = 0;

	while (dist[total] == 0 && head < tail) {
		for (m = *head++, i = 0; i < n; i++) {
			if ((m + len[i]) > total || dist[m + len[i]] != 0)
				continue;

			if (memcmp(goal+m, str[i], len[i]) != 0)
				continue;

			dist[*tail++ = (m + len[i])] = dist[m] + 1;
		}
	}

	return (dist[total] - 1);
}

void rev(char *q, char *p)
{
	int i;

	for (i = strlen(p) - 1; i >= 0; i--)
		*q++ = p[i];
	*q++ = '\0';
}

int main()
{
	int i, t, r;

	scanf("%d", &r);

	for (t = 1; t <= r; t++) {
		scanf(" %s %d", goal, &n);
		total = strlen(goal);

		for (i = 0; i < n; i++) {
			scanf(" %s", str[i]);
			len[i] = strlen(str[i]);
		}

		for (i = 0; i < n; i++) {
			rev(str[n + i], str[i]);
			len[n + i] = len[i];
		}
		n *= 2;

		i = solve();
		printf((i < 0) ? "Set %d: Not possible.\n" : "Set %d: %d.\n", t, i);	
	}

	return 0;
}
