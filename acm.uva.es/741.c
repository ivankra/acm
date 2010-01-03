#include <stdio.h>
#include <string.h>

/* column 0 is copy of column n */
static char data[512][512];
static int n;

/* Completes table in data, given first and last column */
static void complete()
{
	int i, col, row;
	register char *p, *q;
	register int j;

	for (col = 2; col < n; col++) {
		for (row = 0; row < n;) {
			/* find all known prefixes starting with text in
			   data[row][1..col-1] and write them below in current
			   column starting */
			for (q = data[row], i = 0; i < n; i++) {
				for (p = data[i], j = 1; j < col; j++, p++)
					if (*p != q[j]) break;

				if (j >= col) {
					data[row++][col] = *p;

					if (row == n ||
					    data[row][col - 1] != q[col - 1])
						break;
				}
			}
		}
	}
}

int main()
{
	static char buf[512];
	static int row, cnt[26], t;
	register int i, j;

	for (t = 0; scanf(" %[A-Za-z] %d", buf, &row) == 2 && row > 0; t++) {
		for (i = 0; buf[i]; i++)
			if (buf[i] >= 'a' && buf[i] <= 'z')
				buf[i] = buf[i] + 'A' - 'a';
			else if (!(buf[i] >= 'A' && buf[i] <= 'Z'))
				break;
		n = i;

		for (i = 0; i < n; i++)
			data[i][0] = data[i][n] = buf[i];

		/* prepare column 1, by sorting letters of given word */

		for (i = 0; i < 26; i++) cnt[i] = 0;
		for (i = 0; i < n; i++) cnt[buf[i] - 'A']++;

		for (i = 0, j = 0; j < 26; j++)
			while (cnt[j]-- > 0) data[i++][1] = j + 'A';

		complete();

		if (t > 0)
			printf("\n");

		data[row - 1][n + 1] = '\0';
		printf("%s\n", &data[row - 1][1]);
	}

	return 0;
}
