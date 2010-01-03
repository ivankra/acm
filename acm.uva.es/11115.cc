#include <cstdio>

int main()
{
	int n, k;
	while (scanf("%d %d", &n, &k) == 2 && n > 0) {
		int a[100];

		for (int i = 0; i < 100; i++) a[i] = 0;
		a[0] = 1;

		for (int i = 0; i < k; i++)
			for (int j = 0, c = 0; j < 100; j++, c /= 10)
				a[j] = (c += a[j] * n) % 10;

		int m = 100;
		while (m > 1 && a[m-1] == 0) m--;

		for (int i = m-1; i >= 0; i--) putchar(a[i]+'0');
		putchar('\n');		
	}
}
