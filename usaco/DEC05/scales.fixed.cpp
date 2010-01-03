/*
TASK: scales
ID: infnty1
LANG: C++
*/
/* Algorithm: backtracking. */
#include <stdio.h>
#include <assert.h>

unsigned s[1024], a[1024], n, c, best;

void go(unsigned k, unsigned x)
{
again:	if (x > best) best = x;
	if (k == 0) return;
	if (x+s[k] <= c) { if (x+s[k] > best) best = x+s[k]; return; }
	if (x == c) { best = c; return; }
	if (x+s[k] <= best || best == c) return;

	if (x+a[k] <= c) go(k-1, x+a[k]);

	/* go(k-1, x); */
	k--; goto again;
}

int main()
{
	freopen("scales.in", "r", stdin);
	freopen("scales.out", "w", stdout);

	scanf("%u %u", &n, &c);
	assert(1 <= n && n <= 1000 && 1 <= c && c < (1<<30));
	for (int i = 1; i <= n; i++) {
		scanf("%u", &a[i]);
		if (i >= 2) assert(a[i-1] <= a[i]);
		if (i >= 3) assert(a[i-1]+a[i-2] <= a[i]);
	}

	while (n > 0 && a[n] > c) n--;
	/*assert(n <= 44);*/

	s[0] = 0;
	for (int i = 1; i <= n; i++) s[i] = s[i-1] + a[i];

	best = 0;
	go(n, 0);

	printf("%u\n", best);
	return 0;
}
