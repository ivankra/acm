#include <stdio.h>
#include <ctype.h>

int pile[64][64], count[64], no;

int match(int p, int q)
{
	p = pile[p][count[p] - 1];
	q = pile[q][count[q] - 1];
	return (((p & 0xFF) == (q & 0xFF)) || ((p & 0xFF00) == (q & 0xFF00)));
}

int reduce()
{
	int i, j, k;

	for (i = 1; i < no; i++) {
		if ((i - 3) >= 0 && match(i - 3, i)) {
			pile[i - 3][count[i - 3]++] = pile[i][--count[i]];
			break;
		}

		if (match(i - 1, i)) {
			pile[i - 1][count[i - 1]++] = pile[i][--count[i]];
			break;
		}
	}

	if (i >= no)
		return 0;

	for (i = k = 0; i < no; i++) {
		if (count[i] == 0)
			continue;

		if (i == k) {
			k++;
			continue;
		}

		for (j = 0; j < count[i]; j++)
			pile[k][j] = pile[i][j];
		count[k] = count[i];

		k++;
	}

	no = k;
	return 1;
}

int get()
{
	static char s[1024];

	if (scanf(" %s", s) != 1 || s[0] == '#')
		return -1;

	return (toupper(s[0]) << 8) | toupper(s[1]);
}

int main()
{
	int s[64], i;

	for (;;) {
		for (i = 0; i < 52 && (s[i] = get()) >= 0; i++);
		if (i < 52) break;

		for (no = i = 0; i < 52; i++) {
			pile[no][0] = s[i];
			count[no] = 1;
			no++;
			while (reduce());
		}

		printf("%d pile%s remaining:", no, (no == 1) ? "" : "s");
		for (i = 0; i < no; i++)
			printf(" %d", count[i]);
		printf("\n");
	}

	return 0;
}
