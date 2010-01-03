#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;
#define REP(i,n) for(int _REP_N=(n),i=0;i<_REP_N;i++)

int check(int x) {
	int k = 0;
	for (int p = 2; k < 2 && p*p <= x; p++) {
		while (x % p == 0) { k++; x /= p; }
	}
	if (x > 1) k++;
	return k==2;
}

int main() {
	int N;
	while (scanf("%d", &N) == 1) {
		int res = 0, x;
		while (N-- > 0 && scanf("%d", &x) == 1)
			res += check(x);
		printf("%d\n", res);
	}
}
