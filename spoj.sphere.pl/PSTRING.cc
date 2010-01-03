#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char X[10010], Y[1024];
int buf[2048], *f=buf, *g=&buf[1024], N, M;
int P[1024], next[1024][256];

int main() {
	while (gets(X) && gets(Y)) {
		N = strlen(X);
		M = strlen(Y);

		P[0] = P[1] = 0;
		for (int i = 2; i <= M; i++) {
			int t;
			for (t = P[i-1]; t > 0 && Y[t] != Y[i-1]; t = P[t]);
			P[i] = (Y[t] == Y[i-1] ? t+1 : 0);
		}

		for (int j = 0; j < M; j++) {
			for (int c = 0; c < 256; c++) next[j][c] = 0;
			for (int t = j; t > 0; t = P[t])
				next[j][Y[t]] >?= t+1;
			next[j][Y[0]] >?= 1;
		}

		for (int j = 0; j < M; j++) f[j] = 1<<20;
		f[0] = 0;

		for (int i = 0; i < N; i++) {
			int c = X[i];
			for (int j = 0; j < M; j++) g[j] = f[j] + 1;
			for (int j = 0; j < M; j++) g[next[j][c]] <?= f[j];
			swap(f, g);
		}

		int res = 1<<20;
		for (int j = 0; j < M; j++)
			res <?= f[j];
		printf("%d\n", res);
	}
}
