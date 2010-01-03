#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;

struct Segment {
	ll x1, y1, x2, y2;
};

bool between(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3)
{
	bool a = (x1 < x2 || (x1 == x2 && y1 < y2));
	bool b = (x2 < x3 || (x2 == x3 && y2 < y3));
	return a == b;
}

int check(const Segment &s, const Segment &t)
{
	ll a1 = s.y2 - s.y1;
	ll b1 = s.x1 - s.x2;
	ll c1 = a1 * s.x1 + b1 * s.y1;

	ll a2 = t.y2 - t.y1;
	ll b2 = t.x1 - t.x2;
	ll c2 = a2 * t.x1 + b2 * t.y1;

	ll det = a1 * b2 - a2 * b1;
	ll xn = c1 * b2 - c2 * b1;
	ll yn = a1 * c2 - a2 * c1;

	if (det != 0) {
		if (det < 0) { det = -det; xn = -xn; yn = -yn; }

		ll x_min = max(min(s.x1, s.x2), min(t.x1, t.x2));
		ll x_max = min(max(s.x1, s.x2), max(t.x1, t.x2));
		ll y_min = max(min(s.y1, s.y2), min(t.y1, t.y2));
		ll y_max = min(max(s.y1, s.y2), max(t.y1, t.y2));

		if (!(x_min*det <= xn && xn <= det*x_max &&
			  y_min*det <= yn && yn <= det*y_max)) {
				  return 0;
		}

		if (s.x1*det == xn && s.y1*det == yn) return 1;
		if (s.x2*det == xn && s.y2*det == yn) return 1;
		if (t.x1*det == xn && t.y1*det == yn) return 1;
		if (t.x2*det == xn && t.y2*det == yn) return 1;

		return 2;
	}

	if (xn != 0 || yn != 0) return 0;

	int res = 0;
	res += between(s.x1, s.y1,  t.x1, t.y1,  s.x2, s.y2);
	res += between(s.x1, s.y1,  t.x2, t.y2,  s.x2, s.y2);
	res += between(t.x1, t.y1,  s.x1, s.y1,  t.x2, t.y2);
	res += between(t.x1, t.y1,  s.x2, s.y2,  t.x2, t.y2);
	return res;
}

int main()
{
	enum { MAXN = 5000 };
	static Segment S[MAXN];

	int T, N;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d", &N) == 1; cs++) {
		assert(N <= MAXN);
		for (int i = 0; i < N; i++) {
			scanf("%lld %lld %lld %lld", &S[i].x1, &S[i].y1, &S[i].x2, &S[i].y2);
		}

		int res = N;
		for (int i = 0; i < N; i++)
			for (int j = i+1; j < N; j++)
				res += check(S[i], S[j]);

		printf("%d\n", res);
		if (cs != T) printf("\n");
	}
}
