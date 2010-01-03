/*
ID: mjf28791
PROG: fact4
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, r, t, two, five;

	freopen("fact4.in", "r", stdin);
	freopen("fact4.out", "w", stdout);

	scanf("%d", &n);

	for (r = 1, two = five = 0; n > 1; n--) {
		for (t = n; (t & 1) == 0; t >>= 1, two++);
		for (; (t % 5) == 0; t /= 5, five++);
		r = (r * t) % 10;
	}

	for (two -= five; two > 0; two--)
		r = (r * 2) % 10;

	printf("%d\n", r);
	return 0;
}
