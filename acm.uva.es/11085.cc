#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;
#define REP(i,n) for(int _REP_N=(n),i=0;i<_REP_N;i++)

vector<string> sol;

char str[100];

void go(int c, int ur, int uf, int ub) {
	if (c == 8) { str[c]=0; sol.push_back(string(str)); return; }

	for (int r = 0; r < 8; r++) {
		if (ur & (1<<r)) continue;
		if (uf & (1<<(r+c))) continue;
		if (ub & (1<<(8-r+c))) continue;

		str[c] = '1' + r;
		go(c+1, ur|(1<<r), uf|(1<<(r+c)), ub|(1<<(8-r+c)));
	}
}

int main() {
	go(0, 0, 0, 0);
	assert(sol.size() == 92);

	for (int cs = 1; ; cs++) {
		for (int i = 0; i < 8; i++) {
			int x;
			if (scanf("%d", &x) != 1) exit(0);
			assert(1 <= x && x <= 8);
			str[i] = '0' + x;
		}

		int best = 8;
		for (int i = 0; i < 92; i++) {
			int res = 8;
			for (int j = 0; j < 8; j++)
				if (sol[i][j] == str[j]) res--;
			best <?= res;
		}
		printf("Case %d: %d\n", cs, best);
	}
}
