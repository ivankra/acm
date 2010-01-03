#include <stdio.h>

int primeq(int n)
{
	int i, s;

	for (s = n; s > 1; s = i)
		if ((i = (s + (n / s)) >> 1) >= s) break;

	for (i = 3, s++; i < n && i <= s; i += 2)
		if ((n % i) == 0) return 0;

	return 1;
}

int main()
{
	int stat[10001], a, b, i;

	stat[0] = 1;
	for (i = 1; i < 10001; i++)
		stat[i] = stat[i - 1] + primeq(i * (i + 1) + 41);

	while (scanf("%d %d", &a, &b) > 0) {
		i = (a <= 0) ? stat[b] : (stat[b] - stat[a - 1]);
		int p = i * 100;
		int q = b - a + 1;
		int r = (p * 200 + q) / (2*q);
		printf("%d.%.2d\n", r/100, r%100);
		//printf("%.2f\n", (double)(i * 100) / (double)(b - a + 1));
	}

	return 0;
}
