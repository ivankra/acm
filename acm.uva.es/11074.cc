#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
using namespace std;
#define REP(i,n) for(int _REP_N=(n),i=0;i<_REP_N;i++)

void ast(int m, int nl = 1, char c = '*') {
	while (m-- > 0) putchar(c);
	if (nl) putchar('\n');
}

int main() {
	int S, T, N;

	for (int cs = 1; scanf("%d %d %d", &S, &T, &N) == 3; cs++) {
		if ((S|T|N)==0) break;

		printf("Case %d:\n", cs);
		REP(i,N) {
			REP(j,T) ast(N*(S+T)+T);
			REP(j,S) {
				REP(k,N) { ast(T,0); ast(S,0,'.'); }
				ast(T);
			}
		}
		REP(j,T) ast(N*(S+T)+T);
		printf("\n");
	}
}
