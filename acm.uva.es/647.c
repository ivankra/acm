#include <stdio.h>
#include <string.h>

int list[1024], jump[128], extra[128], loc[8], mov[8], n;

void dprintf(char *s,...){}

int solve()
{
	int i, p, q;

	memset(loc, 0, sizeof(loc));
	memset(mov, 0, sizeof(mov));

	for (p = 0, q = n - 1;;) {
		dprintf("\n%4d:",p);
		for(i=0;i<n;i++)dprintf((i==0)?" (%d":",%d",loc[i]);
		dprintf(")  ");

		if (mov[q] > 0) {
			mov[q] = 0;
		} else {
			q = (q + 1) % n;
			while (mov[q] < 0) {
				mov[q] = 0;
				q = (q + 1) % n;
			}
		}
		dprintf(" Q=%d ",q);

		i = loc[q] + list[p++];
		dprintf(" %d->%d",loc[q],i);
		if (i == 100) {
			dprintf("\n");
			return (q + 1);
		}

		if (i > 100)
			continue;

		loc[q] = i;
		if (extra[i]) {
			mov[q] = extra[i];
			dprintf("  <%d>",extra[i]);
			continue;
		}

		while (jump[loc[q]]) {
			dprintf(" -> %d",jump[loc[q]]);
			loc[q] = jump[loc[q]];
		}
	}
}

int main()
{
	int i, x, y;

	for (i = 0; scanf("%d", &list[i]) == 1 && list[i] != 0; i++);

	while (scanf("%d", &n) == 1 && n > 1) {
		memset(jump, 0, sizeof(jump));
		while (scanf("%d %d", &x, &y) == 2 && x > 0)
			jump[x] = y;

		memset(extra, 0, sizeof(extra));
		while (scanf("%d", &x) == 1 && x != 0)
			if (x > 0)
				extra[x] = 1;
			else
				extra[-x] = -1;

		printf("%d\n", solve());
	}

	return 0;
}
