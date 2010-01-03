#include <cstdio>
#include <cctype>
typedef unsigned long long u64;

int N, op[1024];

int f(int x) {
	static int s[1024], m;

	m = 0;
	for (int i = 0; op[i] != '%'; i++) {
		if (op[i] <= 0) {
			s[++m] = -op[i];
		} else if (op[i] == 'x') {
			s[++m] = x;
		} else if (op[i] == '+') {
			m--;
			s[m] += s[m+1];
			while (s[m] >= N) s[m] -= N;
		} else if (op[i] == '-') {
			m--;
			s[m] = s[m+1] + N - s[m];
			while (s[m] >= N) s[m] -= N;
		} else if (op[i] == '*') {
			m--;
			s[m] = ((u64)s[m+1] * (u64)s[m]) % N;
		} else if (op[i] == 'n') {
			s[++m] = 0;
		}
	}
	return s[m-1] % N;
}

int main() {
	int n;
	char s[1024];
	while (scanf("%d %d", &N, &n) == 2 && N > 0) {
		for (int i = 0; scanf(" %s", s) == 1; i++) {
			if (isdigit(s[0])) {
				sscanf(s, "%d", &op[i]);
				op[i] = -(op[i] % N);
			} else {
				op[i] = tolower(s[0]);
			}
			if (s[0] == '%') break;
		}

		n %= N;

		int alpha = n, beta = n;
		do {
			alpha = f(f(alpha));
			beta = f(beta);
		} while (alpha != beta);

		alpha = f(alpha);
		for (n = 1; alpha != beta; n++) alpha = f(alpha);

		printf("%d\n", n);
	}
}
