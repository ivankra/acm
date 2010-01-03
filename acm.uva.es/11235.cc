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

int N, Q;
int a[150000], b[150000], start[150000], next[150000];

int build(int lo, int hi)
{
	if (lo == hi) return a[lo];

	int mid = (lo + hi) / 2;
	b[mid] = build(lo, mid);
	b[mid] >?= build(mid+1, hi);
	return b[mid];
}

int query(int lo, int hi, int l, int r)
{
	if (l < lo) l = lo;
	if (r > hi) r = hi;
	if (l > r) return -999999;
	if (lo == hi) return a[lo];

	int mid = (lo + hi) / 2;
	if (lo == l && hi == r)
		return b[mid];

	return max(query(lo, mid, l, r), query(mid+1, hi, l, r));
}

int main() {
	while (scanf("%d %d", &N, &Q) == 2 && N > 0) {
		for (int i = 0; i < N; i++) {
			scanf("%d", &a[i]);
			if (i > 0) assert(a[i-1] <= a[i]);
		}

		start[0] = 0;
		b[0] = 1;
		for (int i = 1; i < N; i++) {
			b[i] = 0;
			start[i] = (a[i] == a[i-1] ? start[i-1] : i);
			b[start[i]]++;
		}

		for (int i = 0; i < N; i++) a[i] = b[start[i]];
		for (int i = 0; i < N; i++) next[i] = start[i] + a[i];

		build(0, N-1);

		int lo, hi;
		while (Q-- > 0 && scanf("%d %d", &lo, &hi) == 2) {
			assert(1 <= lo && lo <= hi && hi <= N);

			lo--; hi--;

			int res = 1;
			res >?= min(hi, next[lo]-1) - lo + 1;
			res >?= hi - max(lo, start[hi]) + 1;
			lo = next[lo];
			hi = start[hi] - 1;

			if (lo <= hi)
				res >?= query(0, N-1, lo, hi);

			printf("%d\n", res);
		}
	}
}
