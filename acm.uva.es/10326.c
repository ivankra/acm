#include <stdio.h>
#include <stdlib.h>

void print64(long long x)
{
	static char buf[32];
	int i;
	if (x < 0) { x = -x; printf("-"); }
	if (x == 0) { printf("0"); return; }
	for (i = 0; x > 0; x /= 10) buf[i++] = '0' + (x % 10);
	while (i-- > 0) putchar(buf[i]);
}

int main()
{
	long long p[64], v;
	int i, j, n, r;

	while (scanf("%d", &n) > 0) {
		for (i = 0; i < 64; i++) p[i] = 0;

		for (i = 0; i < n; i++) {
			scanf("%d", &r);

			if (i == 0) {
				p[0] = -r;
				p[1] = 1;
				continue;
			}

			for (j = (i + 1); j > 0; j--)
				p[j] = p[j - 1] - p[j] * (long long)r;
			p[0] *= -(long long)r;
		}

		for (i = 63, j = 0; i > 0; i--) {
			if ((v = p[i]) == 0)
				continue;

			if (j == 0) {
				if (v < 0) { printf("-"); v = -v; }
			} else {
				if (v < 0) { printf(" - "); v = -v; }
				else { printf(" + "); }
			}

			if (v != 1)
				print64(v);

			printf("x");
			if (i > 1) printf("^%d", i);

			j++;
		}

		if (j == 0) {
			print64(p[0]);
		} else {
			v = p[0];
			if (v < 0) {
				printf(" - ");
				v = -v;
			} else {
				printf(" + ");
			}
			print64(v);
		}

		printf(" = 0\n");
	}

	return 0;
}
