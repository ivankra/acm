#include <cstdio>
#include <cstring>

char a[1000010];

int main() {
	memset(a, 0, sizeof(a));

	int n, x;
	for (scanf("%d", &n); n-- > 0 && scanf("%d", &x) == 1;) a[x] ^= 1;

	for (n = 0; a[n]==0; n++);
	printf("%d\n", n);
}
