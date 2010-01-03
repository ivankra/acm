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

int a[100100], N;
int b[100100];

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d", &N) == 1; cs++) {
		REP(i,N) scanf("%d", &a[i]);

		b[N-1] = a[N-1];
		for (int i = N-2; i >= 0; i--)
			b[i] = min(a[i], b[i+1]);

		int res = a[0] - b[1];
		REP(i, N-1)
			res >?= a[i] - b[i+1];
		printf("%d\n", res);

	}
}
