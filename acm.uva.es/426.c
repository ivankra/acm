#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct rec {
	int no, m1, m2;
	char date[9];
};

int compare(const void *p, const void *q)
{
	return ((((struct rec *)p)->no > ((struct rec *)q)->no) ? 1 : -1);
}

int main()
{
	static struct rec r[16384];
	static char buf[1024], s[1024];
	int i, k, n, t, nrows, col, row;

	scanf("%d\n\n", &t);

	while (t-- > 0) {
		for (n = 0; gets(buf) != NULL; n++) {
			s[0] = '\0';

			if (sscanf(buf, " %[0-9/] %d %[0-9.]", r[n].date,
				   &r[n].no, s) < 2)
				break;

			for (i = 0, r[n].m1 = 0; s[i] && s[i] != '.'; i++)
				if (isdigit(s[i]))
					r[n].m1 = r[n].m1 * 10 + s[i] - '0';

			for (r[n].m2 = 0, k = 0; s[i]; i++)
				if (isdigit(s[i]) && ++k <= 2)
					r[n].m2 = r[n].m2 * 10 + s[i] - '0';
		}

		qsort(r, n, sizeof(struct rec), &compare);

		nrows = (n + 2) / 3;

		for (row = 0; row < nrows; row++) {
			for (col = 0; col < 3; col++) {
				k = col * nrows + row;
				if (k >= n) break;

				if (k >= 1 && r[k].no != (r[k - 1].no + 1))
					i = '*';
				else
					i = ' ';

				printf("%s%4d%c %6d.%.2d %s",
					col ? "   " : "", r[k].no, i,
					r[k].m1, r[k].m2, r[k].date);
			}
			printf("\n");
		}

		if (t > 0)
			printf("\n");
	}

	return 0;
}
