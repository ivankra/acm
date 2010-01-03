#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
	int a, b;
	scanf("%d %d", &a, &b);
	for (int n = 0; n < 50; n++) {
		if (a > b) swap(a, b);
		if (a == 0) { printf("%d\n", n); return 0; }
		a *= 2;
		b -= a/2;
	}
	printf("-1\n");
}
