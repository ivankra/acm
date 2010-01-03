#include <cstdio>

int main() {
	int n;
	scanf("%d", &n);

	int f = 1, s;
	for (s = 1; n > s*s; s++) n -= s * s, f += s;
	while (n > s) n -= s, f++;

	printf("%d %d\n", f, n);
}
