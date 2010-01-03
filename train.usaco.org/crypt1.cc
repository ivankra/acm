/*
ID: infnty1
PROB: crypt1
LANG: C++
*/
#include <stdio.h>
#include <string.h>

int allowed[16];

int chk(int n, int w)
{
	for (int i = 0; i < w; i++, n /= 10)
		if (n == 0 || !allowed[n % 10]) return 0;
	return (n == 0);
}

int main()
{
	int n, x;

	freopen("crypt1.in", "r", stdin);
	freopen("crypt1.out", "w", stdout);

	memset(allowed, 0, sizeof(allowed));
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		allowed[x] = 1;
	}

	int r = 0;
	for (int a = 100; a <= 999; a++) {
		if (!chk(a, 3)) continue;
		for (int b = 10; b <= 99; b++) {
			if (!chk(b, 2)) continue;
			int c = a * (b % 10);
			int d = (b / 10) * a;
			if (!chk(c, 3) || !chk(d, 3)) continue;
			int e = a * b;
			if (!chk(e, 4)) continue;
			r++;
		}
	}

	printf("%d\n", r);
	return 0;
}
