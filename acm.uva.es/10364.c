#include <stdio.h>
#include <string.h>

static int a[32], side, n;
static unsigned imp[32768];

static int try(int s, int use)
{
	int i;

	if ((imp[use >> 5] >> (use & 31)) & 1)
		return 0;

	imp[use >> 5] |= 1 << (use & 31);

	if (s > side)
		return 0;

	if ((use + 1) == (1 << n))
		return 1;

	if (s == side)
		s = 0;

	for (i = 0; i < n; i++)
		if (((use >> i) & 1) == 0 && try(s + a[i], use | (1 << i)))
			return 1;

	return 0;
}

int solve()
{
	int i;

	for (side = 0, i = 0; i < n; i++)
		side += a[i];

	if ((side % 4) != 0)
		return 0;

	side /= 4;

	memset(imp, 0, sizeof(imp));

	return try(0, 0);
}

int main()
{
	int i, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);

		printf(solve() ? "yes\n" : "no\n");
	}

	return 0;
}
