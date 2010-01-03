#include <cstdio>
typedef long long i64;

int N, A, B;
int f(int x) { return ((i64)A*(((i64)x*(i64)x)%(i64)N) + (i64)B) % N; }

int main() {
	while (scanf("%d %d %d", &N, &A, &B) == 3 && N > 0) {
		int x = 0, y = 0;
		do { x = f(x); y = f(f(y)); } while (x != y);

		int n = 0;
		do { y = f(y); n++; } while (x != y);
		printf("%d\n", N - n);
	}
}
