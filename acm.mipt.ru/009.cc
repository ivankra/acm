#include <cstdio>
#include <cstring>

int main()
{
	int a[1024], b[1024], n;

	scanf("%d", &n);
	if (n <= 1) { printf("1\n"); return 0; }

	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	a[0] = b[0] = 1;

	for (int k = 1; k < n; k++) {
		int c = 0;
		for (int i = 0; i < 1024; i++, c /= 10) {
			c += a[i] + b[i];
			a[i] = b[i];
			b[i] = c % 10;
		}
	}

	int i;
	for (i = 1023; b[i] == 0; i--);

	while (i >= 0) putchar('0' + b[i--]);
	printf("\n");
}
