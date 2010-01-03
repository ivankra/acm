#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>
using namespace std;

enum { MAXN = 256 };

// Returns maximum-cost matching
template<typename T>
void kuhnMunkres(int mx[], T a[MAXN][MAXN], int N) {
	T lx[MAXN], ly[MAXN];
	int my[MAXN], px[MAXN], py[MAXN], stk[MAXN];

	assert(0 <= N && N <= MAXN);
	if (N == 0) return;

	for (int i = 0; i < N; i++) {
		lx[i] = a[i][0];
		for (int j = 0; j < N; j++)
			if (a[i][j] > lx[i]) lx[i] = a[i][j];
		ly[i] = 0;
		mx[i] = my[i] = -1;
	}

	// invariant: lx[i] + ly[i] >= a[i][j]
	for (int size = 0; size < N;) {
		int s, t = -1, m = 0;
		for (s = 0; mx[s] != -1; s++);

		stk[m++] = s;
		for (int i = 0; i < N; i++) px[i] = py[i] = -1;
		px[s] = s;

		while (m > 0) {
			int x = stk[--m];
			for (int y = 0; y < N; y++) {
				if (lx[x] + ly[y] == a[x][y] && py[y] == -1) {
					py[y] = x;
					if (my[y] == -1) {
						t = y;
						m = 0;
						break;
					}

					px[my[y]] = y;
					stk[m++] = my[y];
				}
			}
		}

		if (t != -1) {
			for (;;) {
				int x = py[t];
				mx[x] = t;
				my[t] = x;
				if (x == s) break;
				t = px[x];
			}
			size++;
		} else {
			T delta;
			bool flag = true;
			for (int x = 0; x < N; x++) {
				if (px[x] == -1) continue;
				for (int y = 0; y < N; y++) {
					if (py[y] != -1) continue;
					if (flag || lx[x] + ly[y] - a[x][y] < delta) {
						flag = false;
						delta = lx[x] + ly[y] - a[x][y];
					}
				}
			}
			assert(!flag && delta > 0);

			for (int i = 0; i < N; i++) {
				if (px[i] != -1) lx[i] -= delta;
				if (py[i] != -1) ly[i] += delta;
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				assert(lx[i] + ly[j] >= a[i][j]);
			if (mx[i] != -1)
				assert(lx[i] + ly[mx[i]] == a[i][mx[i]]);
		}
	}

	// Verify optimality
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			assert(lx[i] + ly[j] >= a[i][j]);
			if (i != j) assert(mx[i] != mx[j]);
		}
		assert(0 <= mx[i] && mx[i] < N);
		assert(lx[i] + ly[mx[i]] == a[i][mx[i]]);
	}
}

int main()
{
	static int mat[MAXN][MAXN];
	for (int cs = 1; cs <= 1000; cs++) {
		int N = rand() % MAXN;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				mat[i][j] = rand() % 1000000;

		printf("Test %d: N=%d\n", cs, N);
		int mx[MAXN];
		kuhnMunkres(mx, mat, N);
	}
}
