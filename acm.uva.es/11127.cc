#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
using namespace std;

const int MaxNodes = 36000;
int tkid[MaxNodes][2], tsuf[MaxNodes], tflag[MaxNodes], tn;

int next(int x, int c) {
	while (x != 0 && tkid[x][c] == 0)
		x = tsuf[x];
	return tkid[x][c];
}

void insert(int word, int len) {
	int x = 0;
	for (int i = 0; i < len; i++) {
		int c = (word >> i) & 1;
		if (tkid[x][c] == 0) {
			assert(tn+1 < MaxNodes);
			tkid[x][c] = tn++;
		}
		x = tkid[x][c];
	}
	tflag[x] = 1;
}

void makesuf() {
	queue<int> q;
	q.push(0);

	while (!q.empty()) {
		int x = q.front();
		q.pop();

		for (int c = 0; c < 2; c++) {
			int y = tkid[x][c];
			if (y == 0) continue;

			if (x == 0) {
				tsuf[y] = 0;
			} else {
				int z = tsuf[x];
				while (z != 0 && tkid[z][c] == 0) {
					z = tsuf[z];
				}
				tsuf[y] = tkid[z][c];
			}

			tflag[y] |= tflag[x] | tflag[tsuf[y]];

			q.push(y);
		}
	}
}

int main()
{
	memset(tkid, 0, sizeof(tkid));
	memset(tsuf, 0, sizeof(tsuf));
	memset(tflag, 0, sizeof(tflag));
	tn = 1;

	for (int n = 1; n <= 10; n++) {
		for (int m = 0; m < (1 << n); m++) {
			insert(m | (m << n) | (m << (n+n)), 3*n);
		}
	}

	makesuf();

	static int f[32][MaxNodes], N;
	char pat[50];

	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		for (int i = 0; i < N; i++) scanf(" %c", &pat[i]);

		for (int x = 0; x < tn; x++)
			f[N][x] = (tflag[x] == 1) ? 0 : 1;

		for (int pos = N-1; pos >= 0; pos--) {
			for (int x = 0; x < tn; x++) {
				f[pos][x] = 0;
				if (tflag[x]) continue;

				for (int c = 0; c < 2; c++) {
					if (pat[pos] != '*' && pat[pos] != '0'+c) continue;
					f[pos][x] += f[pos+1][next(x, c)];
				}
			}
		}

		printf("Case %d: %d\n", cs, f[0][0]);
	}
	
}
