#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

class Summator {
	vector<int> a;

	int sum(int k) const {
		int res = 0;
		for (k = min(k, size()); k > 0; k &= k-1)
			res += a[k];
		return res;
	}

public:
	Summator(int N) { a = vector<int>(N+1); }
	int size() const { return a.size()-1; }
	int sum(int a, int b) const { return sum(b) - sum(a-1); }

	void add(int k, int val) {
		assert(1 <= k && k <= size());
		for (int n = size(); k <= n; k += k&~(k-1))
			a[k] += val;
	}
};
