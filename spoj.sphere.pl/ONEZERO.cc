#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;

#define Z 64

struct state {
	int r;
	unsigned a[Z/32];
};

int got[32768], id=42, n, m, t, T;

void solve()
{
	vector<state> Q;
	state s;

	memset(&s, 0, sizeof(s));
	Q.push_back(s);

	id++;

	for (m = 0, t = 1;; m++, t = (t * 10) % n) {
		assert(m+3 < Z);
		for (int i = Q.size()-1; i >= 0; i--) {
			if (got[(Q[i].r + t) % n] == id) continue;
			s = Q[i];
			s.r = (s.r + t) % n;
			got[s.r] = id;
			s.a[m >> 5] |= 1U << (m & 31);
			if (s.r == 0) goto done;
			Q.push_back(s);
		}
	}

done:
/*{ static int T=-1, W=0; if (T < 0) T = clock(); W >?= m;
printf("%6d %6d %3d ",n,clock()-T,W); }*/
	for (; m >= 0; m--)
		putchar(((s.a[m >> 5] >> (m & 31)) & 1) + '0');
	putchar('\n');
}

int main()
{
	memset(got, 0, sizeof(got));
	for (scanf("%d", &T); T-- > 0 && scanf("%d", &n) == 1;) solve();
	return 0;
}
