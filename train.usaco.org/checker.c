/*
ID: infnty1
PROB: checker
LANG: C
*/
#include <stdio.h>

int n, count, forw, backw, prev[32], next[32], col[32];

static void look(int r)
{
	int c;

	if (r > n) {
		if (count >= 3) return;
		for (c = 1; c <= n; c++)
			printf((c < n) ? "%d " : "%d\n", col[c]);
		count++;
		return;
	}

	for (c = next[0]; c; c = next[c]) {
		if (((forw >> (r+c)) | (backw >> (n-r+c))) & 1) continue;

		col[r] = c;

		forw |= 1 << (r+c);
		backw |= 1 << (n-r+c);

		next[prev[next[c]] = prev[c]] = next[c];
		look(r+1);
		prev[next[c]] = next[prev[c]] = c;

		forw ^= 1 << (r+c);
		backw ^= 1 << (n-r+c);

		if (count == 3) break;
	}
}

static void go(int r)
{
	int c;

	if (r == n) {
/*		for (c = next[0]; c; c = next[c])
			count += 1 - (((forw >> (n+c)) | (backw >> c)) & 1);*/
		c = next[0];
		count += 1 - (((forw >> (n+c)) | (backw >> c)) & 1);
		return;
	}

	for (c = next[0]; c; c = next[c]) {
		if (((forw >> (r+c)) | (backw >> (n-r+c))) & 1) continue;

		forw |= 1 << (r+c);
		backw |= 1 << (n-r+c);

		next[prev[next[c]] = prev[c]] = next[c];
		go(r+1);
		prev[next[c]] = next[prev[c]] = c;

		forw ^= 1 << (r+c);
		backw ^= 1 << (n-r+c);
	}
}

static void go1(int c)
{
	forw = 1 << (1 + c);
	backw = 1 << (n - 1 + c);

	next[prev[next[c]] = prev[c]] = next[c];
	go(2);
	prev[next[c]] = next[prev[c]] = c;
}

int main()
{
	int i;

	freopen("checker.in", "r", stdin);
	freopen("checker.out", "w", stdout);

	scanf("%d", &n);

	for (i = 0; i <= n; i++) {
		prev[i] = i - 1;
		next[i] = i + 1;
	}
	forw = backw = count = prev[0] = next[n] = 0;

	look(1);

	for (count = 0, i = 1; (2 * i) <= n; i++)
		go1(i);
	count *= 2;
	if ((n % 2) == 1)
		go1(((n - 1) / 2) + 1);

	printf("%d\n", count);

	return 0;
}
