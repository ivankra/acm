#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

// Generic segments tree.
// Implemented as a heap-like structure.
template<typename Tp> class SegTree {
	vector<Tp> A;
	int K, N, S;

	// Op must be an associative binary function (e.g: min, max, +, *)
	static inline Tp Op(const Tp &a, const Tp &b) {
		return a + b;
	}

public:
	SegTree(int n, const Tp &val) { *this = vector<Tp>(n, val); }
	SegTree(const vector<Tp> &data) { *this = data; }

	// Creates data structure from given elements.  O(n)
	SegTree &operator =(const vector<Tp> &data) {
		N = data.size();
		for (K = 1; K < N; K *= 2);
		A = vector<Tp>(S=K+N);
		for (int i = 0; i < N; i++)
			A[K+i] = data[i];
		for (int i = K-1; i >= 1; i--) {
			if (2*i < S) A[i] = A[2*i];
			if (2*i+1 < S) A[i] = Op(A[i], A[2*i+1]);
		}
		return *this;
	}

	// Returns value of the i-th element
	const Tp &operator[](int i) const { return A[K+i]; }

	// Returns number of elements in data structure
	int size() const { return N; }

	// Changes the value of i-th element (i=0..N-1).  O(log n).
	void set(int i, const Tp &val) {
		assert(0 <= i && i < N);
		int t = K+i;
		for (A[t] = val; (t >>= 1) >= 1;)
			A[t] = (2*t+1<S) ? Op(A[2*t], A[2*t+1]) : A[2*t];
	}

	// Computes Op(val[a], Op(val[a+1], Op(..., val[b]))),
	// where val[i]=value of i-th element.  O(log n).
	Tp eval(int a, int b) const {
		assert(0 <= a && a <= b && b < N);

		if (a == b) return A[K+a];

		Tp L = A[K+a];
		for (int i=K+a, j=K+b; (i>>1) != (j>>1); i>>=1, j>>=1)
			if ((i&1)==0 && i+1 < S) L = Op(L, A[i+1]);

		Tp R = A[K+b];
		for (int i=K+a, j=K+b; (i>>1) != (j>>1); i>>=1, j>>=1)
			if ((j&1)==1) R = Op(A[j-1], R);

		return Op(L, R);
	}
};




// addition of strings is associative, and not commutative

int rnd(int a, int b) { return a + (rand() % (b-a+1)); }

string rnd_str() {
	string s;
	int m = rnd(1, 5);
	for (int j = 0; j < m; j++)
		s += (char)rnd('a', 'z');
	return s;
}

int main() {
	for (int cs = 1; cs <= 100; cs++) {
		int N = rnd(1, 20);

		printf("Test %d: N=%d\n", cs, N);
		fflush(stdout);

		int INF = 0x3fffffff;

		vector<string> v;
		for (int i = 0; i < N; i++)
			v.push_back(rnd_str());

		SegTree<string> m = v;

		for (int q = 0; q < 100; q++) {
			for (int u = 0; u < 3*N; u++) {
				int pos = rnd(0, N-1);
				string val = rnd_str();
				v[pos] = val;
				m.set(pos, val);
				assert(m.eval(pos, pos) == val && m[pos] == val);
			}

			for (int a = 0; a < N; a++)
				assert(m[a] == v[a]);

			for (int a = 0; a < N; a++) {
				string res = v[a];
				for (int b = a; b < N; b++) {
					if (b != a) res = res + v[b];
					assert(m.eval(a, b) == res);
				}
			}
		}

	}

	printf("All passed.\n");
}
