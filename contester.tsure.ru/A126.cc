#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int pw(int x, int y, int m) {
	int res = 1;
	for (; y > 0; y >>= 1) {
		if (y & 1) res = (res * x) % m;
		x = (x * x) % m;
	}
	return res;
}

int main()
{
	int n, m, r;
	scanf("%d %d %d", &n, &m, &r);

	int k = 0;
	for (int x = 0; x < m; x++)
		if (pw(x, n, m) == r) printf(k++ == 0 ? "%d" : " %d", x);
	if (k == 0) printf("-1");
	printf("\n");
}
