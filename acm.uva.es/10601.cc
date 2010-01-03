// Polya-Burnside counting
#include <cstdio>
#include <cstring>
#include <cassert>

long long choose[32][32];
int cnt[8];

int main()
{
	int T;
	scanf("%d", &T);

	memset(choose, 0, sizeof(choose));
	for (int n = 0; n < 32; n++) {
		choose[n][0] = 1;
		for (int k = 1; k <= n; k++)
			choose[n][k] = choose[n-1][k-1] + choose[n-1][k];
	}

	for (int cs = 1; cs <= T; cs++) {
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < 12; i++) {
			int x;
			scanf("%d", &x);
			assert(1 <= x && x <= 6);
			cnt[x-1]++;
		}

		long long res1 = 1;
		for (int m = 12, i = 0; i < 6; i++) {
			res1 *= choose[m][cnt[i]];
			m -= cnt[i];
		}

		long long res2 = 0;
		for (int c1 = 0; c1 < 6; c1++) {
			if (cnt[c1] == 0) continue;
			cnt[c1]--;
			for (int c2 = 0; c2 < 6; c2++) {
				if (cnt[c2] == 0) continue;
				cnt[c2]--;

				long long t = 1;
				for (int m = 10/2, i = 0; i < 6; i++) {
					if (cnt[i] % 2 != 0) { t = 0; break; }
					t *= choose[m][cnt[i]/2];
					m -= cnt[i]/2;
				}
				res2 += t;

				cnt[c2]++;
			}
			cnt[c1]++;
		}

		long long res3 = 1;
		long long res4 = 1;
		long long res5 = 1;

		for (int m = 12/2, i = 0; i < 6; i++) {
			if (cnt[i] % 2 != 0) { res3 = 0; break; }
			res3 *= choose[m][cnt[i]/2];
			m -= cnt[i]/2;
		}

		for (int m = 12/3, i = 0; i < 6; i++) {
			if (cnt[i] % 3 != 0) { res4 = 0; break; }
			res4 *= choose[m][cnt[i]/3];
			m -= cnt[i]/3;
		}

		for (int m = 12/4, i = 0; i < 6; i++) {
			if (cnt[i] % 4 != 0) { res5 = 0; break; }
			res5 *= choose[m][cnt[i]/4];
			m -= cnt[i]/4;
		}

		long long res = (res1 + 6*res2 + 3*res3 + 8*res4 + 6*res5) / 24;
		printf("%lld\n", res);
	}
}

/*
Permutation group elements' cycles:
1 x  1 1 1 1 1 1 1 1 1 1 1 1 
6 x  1 1 2 2 2 2 2 
3 x  2 2 2 2 2 2 
8 x  3 3 3 3 
6 x  4 4 4 
*/

/*
typedef vector<int> VI;
typedef vector<VI> VVI;
VI rot(VI v, int way) {
	static char *cmd[3] = {
		"abcda efghe lkjil ",
		"aleia ckgjc dbfhd ",
		"flbkf hidjh eacge "
	};
	char *p = cmd[way];
	VI w = v;
	for (; *p; p++) {
		if (isspace(p[0]) || p[1] == 0 || isspace(p[1])) continue;
		int x = p[0] - 'a';
		int y = p[1] - 'a';
		w[y] = v[x];
	}
	return w;
}

int cyc[50], ncyc, cnt[50];

int main()
{
	VVI G;

	VI perm(12);
	for (int i = 0; i < 12; i++) perm[i] = i;

	G.push_back(perm);

	for (int i = 0; i < (int)G.size(); i++) {
		perm = G[i];
		for (int x = 0; x < 4; x++, perm = rot(perm, 0)) {
			for (int y = 0; y < 4; y++, perm = rot(perm, 1)) {
				for (int z = 0; z < 4; z++, perm = rot(perm, 2)) {
					if (find(G.begin(), G.end(), perm) == G.end()) {
						G.push_back(perm);
					}
				}
			}
		}
	}
	assert(G.size() == 24);

	for (int i = 0; i < 24; i++) {
		perm = G[i];
		ncyc = 0;
		for (int j = 0; j < 12; j++) {
			if (perm[j] == -1) continue;
			cyc[ncyc] = 0;
			for (int x = j; perm[x] != -1;) {
				int y = perm[x];
				perm[x] = -1;
				x = y;
				cyc[ncyc]++;
			}
			ncyc++;
		}

		sort(cyc, cyc+ncyc);
		for (int j = 0; j < ncyc; j++) printf("%d ", cyc[j]);
		printf("\n");
	}
}
*/
