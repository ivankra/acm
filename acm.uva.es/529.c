#include <stdio.h>
#include <string.h>

int chain[65536], avail[65536], len, flimit, fnext, goal;

static int find()
{
	int i, j, f;

	if (chain[len - 1] == goal)
		return 1;

	for (f = len, i = chain[len - 1]; (2 * i) <= goal; f++, i *= 2);

	i = goal - i;
	if (i > 0) {
		f += 2;
		for (j = 0; j < len; j++)
			if (chain[j] == i) { f--; break; }
	}

	if (f > flimit) {
		if (f < fnext) fnext = f;
		return 0;
	}

	i = 2 * chain[len - 1];
	if (i > goal) i = goal;

	for (; i > chain[len - 1]; i--) {
		if (!avail[i]) continue;

		chain[len++] = i;
		for (j = 0; j < len; j++)
			avail[i + chain[j]]++;

		if (find()) return 1;

		for (j = 0; j < len; j++)
			avail[i + chain[j]]--;
		len--;
	}

	return 0;
}

int main()
{
	int i;

	while (scanf("%d", &goal) == 1 && goal > 0) {
		fnext = 0;

		for (;;) {
			chain[0] = 1;
			len = 1;

			flimit = fnext;
			fnext = 0x7FFFFFFF;

			memset(avail, 0, sizeof(avail));
			avail[2] = 1;

			if (find()) break;
		}

		for (i = 0; i < len; i++)
			printf(((i + 1) < len) ? "%d " : "%d\n", chain[i]);
	}

	return 0;
}
