#include <cstdio>

int main() {
	int T, n, m;
	for (scanf("%d", &T); T-- > 0 && scanf("%d %d", &n, &m) == 2;)
		printf("%d\n", (n/3)*(m/3));
}
