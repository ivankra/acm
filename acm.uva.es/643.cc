#include <cstdio>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <vector>
#include <set>
using namespace std;
#define REP(i,n) for(int _REP_N=(n),i=0;i<_REP_N;i++)

int cnt[100000];

int main() {
	char buf[1024];
	set<string> inv_s;
	vector<string> inv;

	memset(cnt, 0, sizeof(cnt));

	while (gets(buf)) {
		int n = strlen(buf);
		while (n > 0 && isspace(buf[n-1])) buf[--n] = 0;

		bool ok = (n == 5);
		REP(i, 5)
			if (!isdigit(buf[i])) ok = false;
		ok &= (atoi(buf) != 0);

		if (!ok) {
			string s = buf;
			if (inv_s.count(s) == 0) {
				inv_s.insert(s);
				inv.push_back(s);
			}
		} else {
			cnt[atoi(buf)]++;
		}
	}

	printf("ZIP         LETTERS     BUNDLES\n\n");

	int totalLet=0, totalBun=0;
	for (int z = 0; z <= 99999; z++) {
		if (cnt[z] < 10) continue;

		int b, l;
		if (cnt[z] < 20) { b = 1; l = min(cnt[z], 15); }
		else { b = (cnt[z]+14)/15; l = cnt[z]; }

		printf("%.5d %10d %11d\n", z, l, b);
		totalBun += b;
		totalLet += l;
		cnt[z] -= l;
	}

	printf("\n");

	for (int z = 0; z <= 99999; z += 100) {
		int c = 0;
		REP(i, 100) c += cnt[z+i];
		if (c < 10) continue;

		int b, l;
		if (c < 20) { b = 1; l = min(c, 15); }
		else { b = (c+14)/15; l = c; }

		printf("%.3dxx %10d %11d\n", z/100, l, b);
		totalBun += b;
		totalLet += l;

		REP(i, 100) {
			int d = min(cnt[z+i], l);
			cnt[z+i] -= d;
			l -= d;
		}
	}

	printf("\n");
	for (int z = 0; z <= 99999; z++) {
		if (cnt[z] > 0) {
			totalLet += cnt[z];
			printf("%.5d %10d %11d\n", z, cnt[z], 0);
		}
	}

	printf("\nTOTALS %9d %11d\n", totalLet, totalBun);

	printf("\nINVALID ZIP CODES\n");
	REP(i, inv.size())
		printf("%s\n", inv[i].c_str());
}
