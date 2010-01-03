#include <stdio.h>

static struct {
	int head, tail, prev, next, count;
	int a[1024];
} team[1024];

static int map[1048576], nteams;

int main()
{
	static char s[1024];
	int i, j, t, x;

	for (t = 1;; t++) {
		scanf("%d", &nteams);
		if (nteams <= 0) break;

		for (i = 1; i <= nteams; i++) {
			scanf("%d", &team[i].count);

			team[i].head = team[i].tail = 0;
			team[i].prev = team[i].next = 0;

			for (j = team[i].count; j-- > 0;) {
				scanf("%d", &x);
				map[x] = i;
			}
		}
		team[0].next = team[0].prev = 0;

		printf("Scenario #%d\n", t);

		while (scanf(" %s", s) == 1) {
			s[0] |= 0x20;

			if (s[0] == 's')
				break;

			if (s[0] == 'e') {
				scanf("%d", &x);
				i = map[x];

				team[i].a[team[i].tail++] = x;

				if (team[i].tail == 1) {
					team[i].prev = team[0].prev;	
					team[team[i].prev].next = i;
					team[i].next = 0;
					team[0].prev = i;
				}
			} else {
				if (team[0].next == 0)
					continue;

				i = team[0].next;
				printf("%d\n", team[i].a[team[i].head++]);

				if (team[i].head < team[i].tail)
					continue;

				team[i].head = team[i].tail = 0;

				team[team[i].prev].next = team[i].next;
				team[team[i].next].prev = team[i].prev;
			}
		}

		printf("\n");
	}

	return 0;
}
