#include <cstdio>

int main()
{
	int n;
	scanf("%d", &n);

	for (int x = 1;; x++) {
		int u = 0;
		n--;
		for (int t = x; t > 0; t /= 10) {
			if (u & (1 << (t % 10))) { n++; break; }
			u |= 1 << (t % 10);
		}
		if (n == 0) {
			printf("%d\n", x);
			return 0;
		}
	}
}
