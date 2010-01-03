#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

bool is_prime[1000];

static inline unsigned get(unsigned state, int i) { return (state >> (4 * i)) & 15; }
void set(unsigned &state, int i, unsigned x) {
	state &= ~(15U << (4 * i));
	state |= (x << (4 * i));
}

void swp(unsigned &state, int i, int j) {
	i *= 4; j *= 4;
	unsigned a = (state >> i) & 15;
	unsigned b = (state >> j) & 15;
	state &= ~(15U << i);
	state &= ~(15U << j);
	state |= a << j;
	state |= b << i;
}

bool is_sorted(unsigned s) {
	for (int i = 1; i < 8; i++)
		if ((get(s, i-1) & 7) > (get(s, i) & 7)) return false;
	return true;
}

bool ok_val(unsigned a, unsigned b) {
	return ((a ^ b) & 8) != 0 && is_prime[(a&7)+(b&7)+2];
}

bool ok(unsigned s, int i) {
	if (i > 0 && ok_val(get(s, i-1), get(s, i))) return true;
	if (i < 7 && ok_val(get(s, i+1), get(s, i))) return true;
	return false;
}

int solve(unsigned v) {
	if (is_sorted(v)) return 0;

	map<unsigned, int> mp;
	mp[v] = 0;

	queue<unsigned> Q;
	Q.push(v);

	while (!Q.empty()) {
		v = Q.front(); Q.pop();
		int vdist = mp[v];

		for (int i = 0; i < 8; i++) {
			unsigned w = v;
			for (int j = i; j > 0;) {
				swp(w, j, j-1);
				j--;

				if (ok(w, j) && mp.count(w) == 0) {
					if (is_sorted(w)) return vdist + 1;
					mp[w] = vdist + 1;
					Q.push(w);
				}
			}

			w = v;
			for (int j = i; j < 7;) {
				swp(w, j, j+1);
				j++;

				if (ok(w, j) && mp.count(w) == 0) {
					if (is_sorted(w)) return vdist + 1;
					mp[w] = vdist + 1;
					Q.push(w);
				}
			}
		}
	}

	return -1;
}

int main()
{
	memset(is_prime, 1, sizeof(is_prime));
	for (int i = 2; i < 1000; i++) {
		if (!is_prime[i]) continue;
		for (int j = i*i; j < 1000; j += i)
			is_prime[j] = false;
	}

	for (int cs = 1;; cs++) {
		unsigned state = 0;
		for (int i = 0; i < 8; i++) {
			int x;
			scanf("%d", &x);
			assert(-8 <= x && x <= 8);
			if (x == 0) exit(0);
			if (x > 0) set(state, i, x-1);
			else set(state, i, (-x-1)+8);
		}
		printf("Case %d: %d\n", cs, solve(state));
	}
}
