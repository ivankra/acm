#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <vector>
using namespace std;
typedef long long i64;

struct state { int r, c, t; i64 mul; };

int a[32][32], n;
i64 w, U[32][32], B[32][32];

void solve()
{
	static i64 R[32][32][2], cnt[128];
	vector<state> Q;
	state s;
	int i, j, k;

	memset(U, 0, sizeof(U));
	memset(B, 0, sizeof(B));
	U[n][n] = B[n][n] = 1;
	for (i = n-1; i >= 1; i--)
		for (j = n; j >= i; j--)
			U[i][j] = U[i][j+1] + U[i+1][j];
	for (i = n; i >= 1; i--)
		for (j = (i == n) ? (i-1) : i; j >= 1; j--)
			B[i][j] = B[i][j+1] + B[i+1][j];

	w %= U[1][1] + B[1][1];

       	s.r = s.c = 1; s.t = 'U'; s.mul = 1; Q.push_back(s);
	s.r = s.c = 1; s.t = 'D'; s.mul = 1; Q.push_back(s);

	while (!Q.empty() > 0) {
		memset(cnt, 0, sizeof(cnt));
		
		for (i = 0; i < Q.size(); i++) {
			i64 s = (Q[i].t == 'U') ?
					U[Q[i].r][Q[i].c] : B[Q[i].r][Q[i].c];
			cnt[a[Q[i].r][Q[i].c]] += Q[i].mul * s;
		}				

		for (i = 'A'; i <= 'Z'; i++) cnt[i] += cnt[i-1];
		for (i = 'A'; i < 'Z' && cnt[i] <= w; i++);
		w -= cnt[i-1];

		putchar(i);

		memset(R, 0, sizeof(R));
		for (j = 0; j < Q.size(); j++) {
			if (a[Q[j].r][Q[j].c] != i) continue;
			if (Q[j].r >= n && Q[j].c >= n) continue;

			if (Q[j].t == 'U') {
				if (Q[j].c+1 <= n) {
					s.r = Q[j].r;
					s.c = Q[j].c+1;
					s.t = 'U';
					R[s.r][s.c][1] += Q[j].mul;
				}

				if (Q[j].r+1 <= Q[j].c) {
					s.r = Q[j].r+1;
					s.c = Q[j].c;
					s.t = 'U';
					R[s.r][s.c][1] += Q[j].mul;
				}
			} else {
				if (Q[j].r >= Q[j].c+1) {
					s.r = Q[j].r;
					s.c = Q[j].c+1;
					s.t = 'B';
					R[s.r][s.c][0] += Q[j].mul;
				}

				if (Q[j].r+1 <= n) {
					s.r = Q[j].r+1;
					s.c = Q[j].c;
					s.t = 'B';
					R[s.r][s.c][0] += Q[j].mul;
				}
			}
		}

		Q.clear();
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				if (R[i][j][1] > 0) {
					s.r = i; s.c = j; s.t = 'U';
					s.mul = R[i][j][1];
					Q.push_back(s);
				}

				if (R[i][j][0] > 0) {
					s.r = i; s.c = j; s.t = 'B';
					s.mul = R[i][j][0];
					Q.push_back(s);
				}
			}
		}
	}
	printf("\n");
}

int main()
{
	int i, j, c, T;

	for (scanf("%d", &T); T-- > 0 && scanf("%d %lld", &n, &w) == 2;) {
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++) {
				while ((a[i][j] = getchar()) != EOF)
					if (isalpha(a[i][j])) break;
				a[i][j] = toupper(a[i][j]);
			}
		solve();
	}
	return 0;
}
