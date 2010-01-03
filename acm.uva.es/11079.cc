#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>
using namespace std;
#define REP(i,n) for(int _REP_N=(n),i=0;i<_REP_N;i++)
typedef long long ll;

template<typename T> T lcm(T a, T b) { return a / __gcd(a, b) * b; }
template<typename T> bool between(T a, T x, T b) { return a <= x && x <= b; }

template<typename T> T floor(T p, T q) {
	assert(q > 0);
	if (p >= 0) return p/q;
	return -(((-p)+q-1)/q);
}

template<typename T> T ceil(T p, T q) {
	assert(q > 0);
	if (p >= 0) return (p+q-1)/q;
	return -((-p)/q);
}

struct Func { int half, per, inc; } f[20];
int N, period, slope[56000];
ll goal, periodInc, periodMax, periodMin;

bool solve() {
	period = 1;
	REP(i, N) period = lcm(period, f[i].per);
	assert(1 <= period && period < 56000);

	REP(i, period) slope[i] = 0;
	REP(i, N) {
		if (f[i].inc == 0) continue;
		for (int t = 0; t < period; t += f[i].per)
			REP(j, f[i].half) slope[t+j] += f[i].inc;
	}

	periodInc = periodMax = periodMin = 0;
	REP(t, period) {
		periodInc += slope[t];
		periodMax >?= periodInc;
		periodMin <?= periodInc;
	}
//printf("period=%d  inc=%lld max=%lld min=%lld  goal=%lld\n", period, periodInc, periodMax, periodMin, goal);

	ll p = 0;
	if (periodInc != 0) {
		ll low, up;
		if (periodInc > 0) {
			low = ceil(goal-periodMax, periodInc);
			up = floor(goal-periodMin, periodInc);
		} else {
			low = ceil(periodMin-goal, -periodInc);
			up = floor(periodMax-goal, -periodInc);
		}

//printf("%lld <= p <= %lld\n", low, up);
		if (low > up || up < 0) return false;
		p = low < 0 ? 0 : low;
	}
//printf("p=%lld   values=[%lld, %lld]\n", p, periodInc*p+periodMin, periodInc*p+periodMax);

	if (!between(periodInc*p+periodMin, goal, periodInc*p+periodMax)) {
assert(periodInc==0);
		return false;
	}

	int y0 = p * periodInc, y1;
	for (int i = 0; i < period; i++, y0 = y1) {
		y1 = y0 + slope[i];
		if (goal < y0 && goal < y1) continue;
		if (goal > y0 && goal > y1) continue;

		double res = period * (double)p + i;
		if (y0 != y1) 
			res += (goal - y0) / (double)(y1 - y0);
		if (res < 0) res = 0;
		printf("%.8f\n", res);
		return true;
	}
	assert(0==1);
	return false;
}

int main() {
	ll K, F;
	for (int cs = 1; scanf("%d %lld", &N, &K) == 2; cs++) {
		if (N==0 && K==0) break;

		assert(1 <= N && N <= 12);
		assert(K >= 0);

		REP(i, N) {
			scanf("%d %d", &f[i].per, &f[i].inc);
			assert(1 <= f[i].per && f[i].per <= 12);
			assert(-100 <= f[i].inc && f[i].inc <= 100);
			f[i].half = f[i].per;
			f[i].per *= 2;
		}

		scanf("%lld", &F);
		goal = F - K;

		printf("Case %d: ", cs);
		if (F < 0 || !solve()) printf("Impossible.\n");
	}
}
