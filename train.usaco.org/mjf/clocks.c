/*
ID: mjf28791
PROG: clocks
LANG: C
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>

int queue[262144], pred[262144], head, tail;
char action[262144];

void check(int s, int p, int a)
{
	if (pred[s] != 0) return;
	pred[s] = p;
	action[s] = a;
	queue[tail++] = s;
}

int apply(int s, char *t)
{
	int i;

	while (*t) {
		i = 2 * (*t++ - 'A');
		s = (s & ~(3 << i)) | ((((s >> i) + 1) & 3) << i);
	}

	return s;
}

int take()
{
	int i, a, r;
	for (r = 0, i = 0; i < 9 && scanf("%d", &a) == 1; i++)
		r |= ((a / 3) & 3) << (2 * i);
	return r;
}

int main()
{
	char *a[] = { "ABDE", "ABC", "BCEF", "ADG", "BDEFH", "CFI", "DEGH", "GHI", "EFHI" };
	char p[1024];
	int i, s;

	freopen("clocks.in", "r", stdin);
	freopen("clocks.out", "w", stdout);

	memset(pred, 0, sizeof(pred));

	head = 0;
	tail = 1;
	queue[0] = take();
	pred[queue[0]] = -1;
	action[queue[0]] = '1';

	while (head < tail && pred[0] == 0) {
		s = queue[head++];
		for (i = action[s] - '1'; i < 9; i++)
			check(apply(s, a[i]), s, '1' + i);
	}

	assert(head < tail);

	for (i = s = 0; i >= 0; i = pred[i])
		p[s++] = action[i];

	for (s--; s-- > 0;)
		printf(s ? "%c " : "%c\n", p[s]);

	return 0;
}
