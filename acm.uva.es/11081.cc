#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
#define REP(i,n) for(int _REP_N=(n),i=0;i<_REP_N;i++)

char s[64], t[64], u[64];
int sn[64][26], tn[64][26], memo[64][64][64][3];

int f(int x, int y, int z, int flag) {
	int &res = memo[x][y][z][flag];
	if (res != -1) return res;

	if (u[z] == 0)
		return res = flag==0 ? 1 : 0;

	res = 0;

	if (flag != 2) {
		int i = sn[x][u[z]-'a'];
		if (i >= 0) {
			res += f(i+1, y, z+1, 0);
			res += f(i+1, y, z, 1);
		}
	}

	if (flag != 1) {
		int i = tn[y][u[z]-'a'];
		if (i >= 0) {
			res += f(x, i+1, z+1, 0);
			res += f(x, i+1, z, 2);
		}
	}

	return (res %= 10007);
}

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf(" %s %s %s", s, t, u);
		memset(sn, 0xff, sizeof(sn));
		memset(tn, 0xff, sizeof(tn));
		for (int i = strlen(s)-1; i >= 0; i--)
			REP(c, 26) sn[i][c] = s[i]=='a'+c ? i : sn[i+1][c];
		for (int i = strlen(t)-1; i >= 0; i--)
			REP(c, 26) tn[i][c] = t[i]=='a'+c ? i : tn[i+1][c];

		memset(memo, 0xff, sizeof(memo));
		printf("%d\n", f(0,0,0,0));
	}
}
