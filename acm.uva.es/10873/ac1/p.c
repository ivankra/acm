#include <stdio.h>
#include <string.h>

int loc[64], w, h;

void push(int c)
{
	loc[c]++;

	if (loc[c - 1] <= (loc[c] - 3) && loc[c + 1] <= (loc[c] - 3)) {
		loc[c] -= 2;
		push(c - 1);
		push(c + 1);
	} else if (loc[c - 1] <= (loc[c] - 3)) {
		loc[c]--;
		push(c - 1);
	} else if (loc[c + 1] <= (loc[c] - 3)) {
		loc[c]--;
		push(c + 1);
	}
}

int main()
{
	static struct { int s, r, c, n, z; } feed[3];
	int i, j, t = 1;

	while (scanf("%d %d", &w, &h) == 2 && w > 0) {
		memset(feed, 0, sizeof(feed));

		for (i = 0; i < 3; i++) {
			scanf("%d", &feed[i].s);
			feed[i].z = (feed[i].s < 1);
		}

		for (i = 0; i < 3; i++) {
			scanf("%d", &feed[i].c);
			feed[i].c++;
			feed[i].r = 0;
		}

		memset(loc, 0, sizeof(loc));
		loc[0] = loc[w + 1] = 0x3FFFFFFF;

		for (;;) {
			for (i = 0; i < 3 && feed[i].z; i++);
			if (i >= 3) break;

			for (j = feed[i++].r; i < 3; i++)
				if (!feed[i].z && feed[i].r < j) j = feed[i].r;

			for (i = 0; i < 3; i++) {
				if (feed[i].z) continue;

				feed[i].r -= j;
				if (feed[i].r > 0) continue;

				feed[i].r = feed[i].s;

				if (loc[feed[i].c] >= h) {
					feed[i].z = 1;
					continue;
				}

				feed[i].n++;
				push(feed[i].c);
			}
		}

		printf("Case %d: %d %d %d %d\n",
			t++, feed[0].n, feed[1].n, feed[2].n,
			w * h - feed[0].n - feed[1].n - feed[2].n);
	}

	return 0;
}
