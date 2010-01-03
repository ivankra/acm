#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int nc, na, cmat[128][128], amat[128][128], id_of[128][128];
char cname[128][8], aname[128][8];

int N, cat[128], an[128];
int cmatch[128], cnext[128], amatch[128], corder[128][128];

int cmp_cat;

bool cmp(int i1, int i2) {
	return cmat[cmp_cat][an[i1]] > cmat[cmp_cat][an[i2]];
}

void solve()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			corder[i][j] = j;
		cmp_cat = cat[i];
		sort(corder[i], corder[i]+N, cmp);
	}

	for (int i = 0; i < N; i++) {
		cmatch[i] = amatch[i] = -1;
		cnext[i] = 0;
	}

	for (;;) {
		bool ok = true;
		for (int i = 0; i < N; i++) {
			if (cmatch[i] >= 0) continue;
			ok = false;

			int j = corder[i][cnext[i]++];
			assert(j < N);

			if (amatch[j] < 0 || amat[an[j]][cat[i]] > amat[an[j]][cat[amatch[j]]]) {
				if (amatch[j] >= 0) cmatch[amatch[j]] = -1;
				amatch[j] = i;
				cmatch[i] = j;
			}
		}
		if (ok) break;
	}

	for (int i = 0; i < N; i++) {
		if (i > 0) printf(" ");
		printf("%s%s", cname[cat[i]], aname[an[cmatch[i]]]);
	}
	printf("\n\n");
}

int main()
{
	for (int cs = 1; scanf("%d", &nc) == 1 && nc > 0; cs++) {
		for (int i = 0; i < nc; i++) {
			scanf(" %s", cname[i]);
			id_of[cname[i][0]][cname[i][1]] = i;
		}

		scanf("%d", &na);
		for (int i = 0; i < na; i++) {
			scanf(" %s", aname[i]);
			id_of[aname[i][0]][aname[i][1]] = i;
		}

		for (int i = 0; i < nc; i++)
			for (int j = 0; j < na; j++)
				scanf("%d", &cmat[i][j]);

		for (int i = 0; i < na; i++)
			for (int j = 0; j < nc; j++)
				scanf("%d", &amat[i][j]);

		for (int sub = 1; scanf("%d", &N) == 1 && N > 0; sub++) {
			for (int j = 0; j < N; j++) {
				char buf[16];
				scanf(" %s", buf);
				cat[j] = id_of[buf[0]][buf[1]];
				an[j] = id_of[buf[2]][buf[3]];
			}

			printf("Scenario %d, Mixture %d:\n", cs, sub);
			solve();
		}
	}
}
