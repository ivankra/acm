#include <cstdio>
#include <cctype>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main()
{
	unsigned long long w[100], ws[100], A, Q;
	int N, NQ;

	while (scanf("%llu %d", &A, &NQ) == 2) {
		if (A == 0 && NQ == 0) break;
		assert(A >= 1);

		w[0] = ws[0] = 0;
		w[1] = ws[1] = 1;
		N = 1;

		while (ws[N] < A) {
			w[N+1] = 2*ws[N] + 1;
			ws[N+1] = ws[N] + w[N+1];
			N++;
			if ((w[N] & (1LL << 63)) != 0) {
				ws[N] = A;
				break;
			}
		}

		printf("%d", N);
		for (int i = 1; i <= N; i++)
			printf(" %llu", w[i]);
		printf("\n");

		for (int i = 0; i < NQ; i++) {
			scanf("%llu", &Q);

			bool first = true;
			int sign = +1;

			int m = N;
			while (Q > 0) {
				assert(Q <= ws[m]);
				if (Q <= ws[m-1]) {
					m--;
					continue;
				}

				if (sign < 0 || !first) putchar(sign > 0 ? '+' : '-');
				first = false;

				printf("%llu", w[m]);

				if (Q >= w[m]) {
					Q -= w[m];
				} else {
					Q = w[m] - Q;
					sign = -sign;
				}
			}
			printf("\n");
		}
	}
}
