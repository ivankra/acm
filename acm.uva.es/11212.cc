#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

#define GET(a, k) (((a) >> (4*(k))) & 15)

int N, case_id, best, bitcnt[1024];
long long queue_buf[370000];
char got[2][1<<19];
char dist[2][1<<19];

// Returns 0-based lexicographic index of input permutation of {0,1,...,N-1}
int encode(long long a) {
	int res = 0, mask = (1 << N) - 1;
	for (int i = 0; i < N; i++) {
		int t = 1 << GET(a, i);
		res = res * (N - i) + bitcnt[mask & (t - 1)];
		mask ^= t;
	}
	return res;
}

void bfs(int flag, long long src, int limit)
{
	long long *head = queue_buf, *tail = queue_buf;
	int enc;
	*tail++ = src;
	enc = encode(src);
	got[flag][enc] = case_id;
	dist[flag][enc] = 0;

	while (head != tail) {
		long long s = *head++;
		enc = encode(s);

		if (flag == 1 && got[0][enc] == case_id) {
			best <?= dist[0][enc] + dist[1][enc];
			continue;
		}

		if (dist[flag][enc] >= limit)
			continue;

		for (int a = 0; a < 4*N; a += 4) {
			for (int len = 4; a+len <= 4*N; len += 4) {
				long long cut = (s >> a) & ((1LL<<len)-1);
				long long t1 = s >> (a + len);
				t1 <<= a;
				t1 |= s & ((1LL << a) - 1);

				for (int b = 0; b <= 4*N-len; b += 4) {
					if (a == b) continue;

					long long t = (t1 & ~((1LL<<b)-1)) << len;
					t |= cut << b;
					t |= (t1 & ((1LL<<b)-1));

					int t_enc = encode(t);
					if (got[flag][t_enc] != case_id) {
						got[flag][t_enc] = case_id;
						dist[flag][t_enc] = dist[flag][enc] + 1;
						*tail++ = t;
					}
				}
			}
		}
	}
}

int main() {
	for (int n = 1; n < 1024; n++)
		bitcnt[n] = 1 + bitcnt[n & (n - 1)];

	for (case_id = 1; scanf("%d", &N) == 1 && N > 0; case_id++) {
		assert(2 <= N && N <= 9);

		long long src = 0, dst = 0;
		for (int i = 0; i < N; i++) {
			int x;
			scanf("%d", &x);
			assert(1 <= x && x <= N);
			src |= ((long long)i) << (4*i);
			dst |= (x-1LL) << (4*i);
		}

		best = 5;
		bfs(0, src, 2);
		bfs(1, dst, 2);
		printf("Case %d: %d\n", case_id, best);
	}
}
