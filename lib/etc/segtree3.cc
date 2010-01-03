#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

template<typename Tp> class SegTree {
	vector<Tp> A, B;
	int N;

	static inline Tp op(const Tp &a, const Tp &b) { return a+b; }

	Tp &upd(int a, int b, int x) {
		assert(0 <= a && a <= b && b < N);
		if (a == b) return A[a];
		int c = (a + b + 1) >> 1;
		if (x < 0 || (a <= x && x <= b)) return B[c] = op(upd(a,c-1,x), upd(c,b,x));
		return B[c];
	}

	inline void upd() { N = A.size(); B = vector<Tp>(N); upd(0,N-1,-1); }

	Tp eval(int a, int b, int qa, int qb) const {
		assert(0 <= a && a <= qa && qa <= qb && qb <= b && b < N);
		if (a == b) return A[a];
		int c = (a + b + 1) >> 1;
		if (a==qa && b==qb) return B[c];
		if (qb < c) return eval(a,c-1,qa,qb);
		if (qa >= c) return eval(c,b,qa,qb);
		return op(eval(a,c-1,qa,c-1), eval(c,b,c,qb));
	}

public:
	SegTree(int n, const Tp &val) { A = vector<Tp>(n, val); upd(); }
	SegTree(const vector<Tp> &V) { A = V; upd(); }
	SegTree &operator =(const vector<Tp> &V) { A = V; upd(); }

	inline int size() const { return N; }
	inline const Tp &operator[](int i) const { return A[i]; }
	inline const Tp &get(int i) const { return A[i]; }
	inline const Tp &set(int i, const Tp &val) { A[i] = val; upd(0,N-1,i); return A[i]; }
	inline Tp eval(int a, int b) const { return eval(0,N-1,a,b); }
};




int rnd(int a, int b) { return a + (rand() % (b-a+1)); }

int main() {
	for (int cs = 1; cs <= 100; cs++) {
		int N = rnd(1, 100);
		printf("Test %d: N=%d\n", cs, N); fflush(stdout);

		vector<int> v;
		for (int i = 0; i < N; i++)
			v.push_back(rnd(-1000000, 1000000));
		SegTree<int> m = v;

		for (int q = 0; q < 100; q++) {
			for (int u = 0; u < 3*N; u++) {
				int pos = rnd(0, N-1);
				int val = rnd(-1000000, 1000000);
				v[pos] = val;
				m.set(pos, val);
				assert(m.eval(pos, pos) == val && m[pos] == val);
			}

			for (int a = 0; a < N; a++) {
				assert(m[a] == v[a]);
				int res = v[a];
				for (int b = a; b < N; b++) {
					if (b != a) res = res + v[b];
					assert(m.eval(a, b) == res);
				}
			}
		}
	}

	printf("All passed.\n");
}

