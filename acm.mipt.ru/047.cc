#include <cstdio>
#define LIM 673500

int F[LIM+1] = { 0, 1, 2, 2, 3, 3 }, p[LIM+1] = { 0, 1, 2 };

int main() {
	for (int k = 2, x = 2; k <= LIM; x++) {
		for (int i = 0; i < F[x] && k <= LIM; i++, k++) {
			F[k] = x;
			p[k] = p[k-1] + F[k-1];
		}
	}

	int n;
	scanf("%d", &n);

	for (int k = 1;; k++)
		if (n < p[k+1]) { printf("%d\n", k); break; }
}
