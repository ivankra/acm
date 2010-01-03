#include <cstdio>
#include <cstring>

char W[8][16], Wu[8][16];
int lead[256], enc[256], used[10], N;

int doit(int m, int carry) {
	if (m == -1) {
		if (carry != 0) return 0;
		for (int i = 'A', k = 0; i <= 'Z'; i++)
			if (enc[i] != -1)
				printf("%s%c=%d", k++?" ":"", i, enc[i]);
		printf("\n");
		return 1;
	}

	for (int i = 0; i < N; i++) {
		if (enc[W[i][m]] != -1) continue;

		int &z = enc[W[i][m]];
		for (z = lead[W[i][m]]; z <= 9; z++) {
			if (used[z]) continue;
			used[z] = 1;
			if (doit(m, carry)) return 1;
			used[z] = 0;
		}
		z = -1;
		return 0;
	}

	int t = carry;
	for (int i = 0; i < N-1; i++)
		t += enc[W[i][m]];
	if (t % 10 == enc[W[N-1][m]]) return doit(m-1, t/10);

	return 0;
}

int main() {
	int T;
	for (scanf("%d", &T); T-- > 0 && scanf("%d", &N) == 1;) {
		for (int i = 0; i < N; i++) scanf(" %[A-Z]", Wu[i]);

		int m = strlen(Wu[0]);
		for (int i = 0; i < N; i++)
			m >?= strlen(Wu[i]);

		for (int i = 0; i < N; i++)
			sprintf(W[i], "%*s", m, Wu[i]);

		memset(enc, 0xff, sizeof(enc));
		enc[' '] = 0;

		memset(lead, 0, sizeof(lead));
		for (int i = 0; i < N; i++)
			if (strlen(Wu[i]) > 1) lead[Wu[i][0]] = 1;

		memset(used, 0, sizeof(used));
		doit(m-1, 0);
	}
}
