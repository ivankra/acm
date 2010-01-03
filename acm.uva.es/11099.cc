#include <cstdio>

int p[20], e[20], k, N;
int mem[1000010];

void Solve() {
	static int all[1000010], ptr[20];

	all[0] = 1;
	for (int i = 0; i < k; i++) ptr[i] = 0;

	int pp = 1;
	for (int i = 0; i < k; i++) pp *= p[i];

	for (int m = 1;; m++) {
		int ans = all[m-1] * pp;
		if (ans >= 2000000) break;

		if (ans > N) {
			mem[N] = ans;
			return;
		}

		all[m] = 0x7fffffff;
		for (int i = 0; i < k; i++) {
			while (ptr[i] < m-1 && all[ptr[i]] * p[i] <= all[m-1])
				ptr[i]++;
			all[m] <?= all[ptr[i]] * p[i];
		}
	}

	mem[N] = -1;
}

void Factorize(int n) {
	k = 0;

	if ((n & 1) == 0) {
		p[0] = 2;
		for (e[0] = 0; (n & 1) == 0; e[0]++) n >>= 1;
		k++;
	}

	for (int d = 3; d * d <= n; d += 2) {
		if (n % d == 0) {
			p[k] = d;
			e[k] = 1;
			for (n /= d; n % d == 0; n /= d) e[k]++;
			k++;
		}
	}

	if (n > 1) {
		p[k] = n;
		e[k] = 1;
		k++;
	}
}

int main() {
	while (scanf("%d", &N) == 1) {
		if (N < 2 || N > 1000000) {
			printf("Not Exist!\n");
			continue;
		}

		Factorize(N);

		if (mem[N] == 0) Solve();

		if (mem[N] < 0)
			printf("Not Exist!\n");
		else
			printf("%d\n", mem[N]);
	}
}
