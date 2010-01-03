#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;
typedef long long ll;

struct Frac {
	int p, q;

	void reduce() {
		if (q < 0) { p = -p; q = -q; }
		int g = __gcd(p < 0 ? -p : p, q);
		p /= g;
		q /= g;
	}

	Frac(int num, int den) : p(num), q(den) { }

	bool operator <(const Frac &other) const {
		return p < other.p || (p == other.p && q < other.q);
	}

	bool operator ==(const Frac &other) const {
		return p == other.p && q == other.q;
	}
};

bool got[128];
vector<Frac> memo[128];

void rec(int mask)
{
	vector<Frac> &res = memo[mask];

	if (got[mask]) return;

	got[mask] = true;
	res.clear();

	for (int L = 1; L < mask; L++) {
		if ((mask & L) != L) continue;

		int R = mask ^ L;
		rec(L);
		rec(R);

		Frac *a = &memo[L][0], *a_end = &memo[L][memo[L].size()];
		Frac *b, *b_begin = &memo[R][0], *b_end = &memo[R][memo[R].size()];
		Frac z(1, 0);

		for (; a != a_end; ++a) {
			for (b = b_begin; b != b_end; ++b) {
				z.p = a->p * b->q + b->p * a->q;
				z.q = a->q * b->q;
				z.reduce();
				res.push_back(z);

				z.p = a->p * b->q - b->p * a->q;
				z.q = a->q * b->q;
				z.reduce();
				res.push_back(z);

				z.p = a->p * b->p;
				z.q = a->q * b->q;
				z.reduce();
				res.push_back(z);

				if (b->p != 0) {
					z.p = a->p * b->q;
					z.q = a->q * b->p;
					z.reduce();
					res.push_back(z);
				}
			}
		}
	}

	sort(res.begin(), res.end());
	res.erase(unique(res.begin(), res.end()), res.end());
}

int main() {
	int N, a[10];

	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		for (int i = 0; i < N; i++) scanf("%d", &a[i]);
		sort(a, a+N);

		memset(got, 0, sizeof(got));
		for (int i = 0; i < 128; i++) memo[i].clear();

		for (int i = 0; i < N; i++) {
			got[1 << i] = true;
			memo[1 << i].push_back(Frac(a[i], 1));
		}

		rec((1 << N) - 1);
		printf("Case %d: %d\n", cs, memo[(1<<N)-1].size());
	}
}
