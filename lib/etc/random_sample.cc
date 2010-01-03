#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

// Generates a simple random sample of size K, on-line,
// from a sequence of unknown length.
template<typename Tp> class random_sample {
	int K, N;
	vector<Tp> A;    // a random sample for the sequence seen so far.

public:
	random_sample(int K) : K(K), N(0) { }

	const vector<Tp> &get() { return A; }

	void put(const Tp &x) {
		N++;
		if (N <= K) {
			A.push_back(x);
		} else if (rand() % N < K) {
			// With probability K/N, a sample of size K from N
			// contains the Nth element. The other elements
			// in this case is a sample of size K-1 from first N-1
			// elements, which can be obtained by deleting
			// a random element from A.

			A[rand() % K] = x;
		}
	}

	template<typename Iter> void put(Iter a, Iter b) {
		for (; a != b; ++a) put(*a);
	}
};



int main() {
	int N = 6, K = 3, T = 100000;
	map<vector<int>, int> mp;

	srand(time(NULL));

	printf("N=%d K=%d  T=%d\n", N, K, T);
	for (int t = 0; t < T; t++) {
		random_sample<int> r(K);
		for (int x = 0; x < N; x++)
			r.put(x);

		vector<int> v = r.get();
		sort(v.begin(), v.end());
		mp[v]++;
	}

	printf("Generated %d distinct samples:\n", mp.size());
	for (map<vector<int>, int>::iterator it = mp.begin(); it != mp.end(); ++it) {
		for (int i = 0; i < K; i++)
			printf(i == 0 ? "%d" : " %d", it->first[i]);
		printf(": %d\n", it->second);
	}
}
