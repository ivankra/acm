#include <cstdio>

int main()
{
	char alpha[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ", s[32];
	int n, k, b;
	while (scanf("%d %d", &n, &b) == 2) {
		for (k = 0; k == 0 || n > 0; n /= b) s[k++] = alpha[n%b];
		while (k-- > 0) putchar(s[k]); putchar('\n');
	}
}
