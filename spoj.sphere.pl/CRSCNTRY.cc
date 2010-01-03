#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> read()
{
	vector<int> v;
	int x;
	while (scanf("%d", &x) == 1 && x != 0)
		v.push_back(x);
	return v;
}

int lcs(const vector<int> &a, const vector<int> &b)
{
	static int f[2][2048];
	int n = a.size(), m = b.size();

	memset(f, 0, sizeof(f));

	int s = 0;
	for (int i = n-1; i >= 0; i--) {
		for (int j = m-1; j >= 0; j--) {
			if (a[i] == b[j]) {
				f[s^1][j] = f[s][j+1] + 1;
			} else {
				f[s^1][j] = max(f[s][j], f[s^1][j+1]);
			}
		}
		s ^= 1;
	}

	return f[s][0];
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		vector<int> a = read();
		int res = 0;
		while (true) {
			vector<int> b = read();
			if (b.size() == 0) break;
			res = max(res, lcs(a, b));
		}
		printf("%d\n", res);
	}
}
