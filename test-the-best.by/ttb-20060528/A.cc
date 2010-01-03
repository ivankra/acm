#include <algorithm>
#include <cstdio>
#include <map>
using namespace std;

map<int, int> M;

struct Garrison {
	int &cnt(int a, int b) {
		if (b < 0) { a = -a; b = -b; }
		if (a == 0 || b == 0) {
			a = b = 0;
		} else {
			int g = __gcd(abs(a), b);
			a /= g; b /= g;
		}
		int t = ((a+1024) << 16) | (b+1024);
		if (M.count(t) == 0) M[t] = 0;
		return M[t];
	}

	long long getCountOfPairs(int x1, int y1, int x2, int y2) {
		M.clear();

		for (int x = x1; x <= x2; x++)
		for (int y = y1; y <= y2; y++)
			cnt(x, y)++;

		long long res = 0;
		for (int x = x1; x <= x2; x++)
		for (int y = y1; y <= y2; y++)
			res += cnt(-x, y);
		return res;
	}
};

int main() {
	printf("%lld [25]\n", Garrison().getCountOfPairs(-2,-2,0,0));
	printf("%lld\n", Garrison().getCountOfPairs(1,2,3,4));
	printf("%lld [2601]\n", Garrison().getCountOfPairs(0,100,50,150));

}
