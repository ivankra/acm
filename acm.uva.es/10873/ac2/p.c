#include <stdio.h>
#include <string.h>

int read(int, char *, int);

int loc[64], w, h;

static void push(int c)
{
	for (;;) {
		loc[c]++;

		if (loc[c - 1] <= (loc[c] - 3) && loc[c + 1] <= (loc[c] - 3)) {
			loc[c] -= 2;
			push(c - 1);
			c++;
		} else if (loc[c - 1] <= (loc[c] - 3)) {
			loc[c]--;
			c--;
		} else if (loc[c + 1] <= (loc[c] - 3)) {
			loc[c]--;
			c++;
		} else {
			return;
		}
	}
}

int main()
{
	static struct { int s, r, c, n, z; } feed[3];
	static char inbuf[1048576];
	static int isdig[256];
	char *inp;
	int i, j, t = 1;

#define READ(x) \
	{ while (!isdig[(int)*inp]) inp++; \
	  for (x = *inp++ - '0'; isdig[(int)*inp];) x = x * 10 + *inp++ - '0'; }

	for (i = 0; i < 256; i++)
		isdig[i] = ('0' <= i && i <= '9');

	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = '\0';

	for (;;) {
		READ(w); if (w == 0) break;
		READ(h);

		memset(feed, 0, sizeof(feed));

		for (i = 0; i < 3; i++) {
			READ(j); feed[i].s = j;
			feed[i].z = (j < 1);
		}

		for (i = 0; i < 3; i++) {
			READ(j);
			feed[i].c = j + 1;
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
