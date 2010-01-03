#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <algorithm>
using namespace std;

int xmi, xpi, xua, N, outn[16];
char *out[16][32768], str[1024];

void doit(int k) {
	if (k >= N) {
		str[N] = 0;
		strcpy(out[N][outn[N]++] = (char *)malloc(N+1), str);
		return;
	}

	for (int c = 0; c < N; c++) {
		if ((xua >> c) & 1) continue;
		if ((xmi >> (c + 15 - k)) & 1) continue;
		if ((xpi >> (c + k)) & 1) continue;

		if (k >= 1) {
			if (abs(str[k-1] - 'A' - c) == 2) continue;
			if (k >= 2 && abs(str[k-2] - 'A' - c) == 1) continue;
		}

		xua ^= 1 << c;
		xmi ^= 1 << (c + 15 - k);
		xpi ^= 1 << (c + k);
		str[k] = 'A' + c;
		doit(k+1);
		xua ^= 1 << c;
		xmi ^= 1 << (c + 15 - k);
		xpi ^= 1 << (c + k);
	}
}

int main() {
	for (N = 1; N <= 15; N++) {
		outn[N] = xmi = xpi = xua = 0;
		doit(0);
//		printf("N=%d: %d\n", N, outn[N]);
	}
	
	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		int ok[16];
		memset(ok, 0, sizeof(ok));
		for (int i = 0; i < N; i++) {
			scanf(" %s", str);
			for (int j = 0; str[j]; j++) {
				if (isupper(str[j])) ok[i] |= 1 << (str[j] - 'A');
				if (str[j] == '?') ok[i] |= (1 << N) - 1;
			}
		}

		long long total = 1;
		for (int i = 0; i < N; i++) {
			int m = 0;
			for (int t = ok[i]; t > 0; t &= t - 1) m++;
			total *= m;
		}

		for (int i = 0; i < outn[N]; i++) {
			char *s = out[N][i];
			total--;
			for (int j = 0; j < N; j++) {
				if (((ok[j] >> (s[j] - 'A')) & 1) == 0) {
					total++;
					break;
				}
			}
		}

		printf("Case %d: %lld\n", cs, total);
	}
}
