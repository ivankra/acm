#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int pf[100], npf, best;

bool isprime(int n) {
	if (n <= 3) return (n >= 2);
	if ((n & 1) == 0) return false;
	for (int p = 3; p*p <= n; p += 2)
		if (n % p == 0) return false;
	return true;
}

void factor(int n) {
	npf = 0;
	while (n > 0 && (n & 1) == 0) { n >>= 1; pf[npf++] = 2; }
	for (int p = 3; p*p <= n; p += 2)
		while ((n % p) == 0) { n /= p; pf[npf++] = p; }
	if (n > 1) pf[npf++] = n;
}

void go(int used, int lastp, long long N);

void go1(int used, int lastp, long long N, int cc, int i) {
	if (N*(cc+1) >= best) return;

	int p = cc+1;
	if (p > lastp && isprime(p)) {
		int u = used;
		long long nn = N*p;
		go(u, p, nn);
		for (int i = 0; i < npf; i++) {
			if (u & (1 << i)) continue;
			if (pf[i] != p) continue;
			u |= 1 << i;
			nn *= p;
			go(u, p, nn);
		}
	}

	while (i < npf) {
		if (used & (1 << i)) { i++; continue; }
		p = pf[i];
		go1(used|(1<<i), lastp, N, cc*pf[i], i);
		while (i < npf && pf[i] == p) i++;
		if (cc == 1) break;
	}
}


void go(int used, int lastp, long long N) {
	if (used == (1<<npf)-1)
		best <?= N;
	go1(used, lastp, N, 1, 0);
}

int main() {
	int n;
	for (int cs = 1; scanf("%d", &n) == 1 && n > 0; cs++) {
		factor(n);
		best = 200000001;
		go(0, 1, 1);
		printf("Case %d: %d %d\n", cs, n, best);
	}
}
