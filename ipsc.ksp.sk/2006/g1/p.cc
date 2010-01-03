#include <cstdio>

int main() {
	int T, n;
	for (scanf("%d", &T); T-- > 0 && scanf("%d", &n) == 1;) {
		printf("%d\n", (n+1)/2);
	}
}
