#include <algorithm>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

struct Fraction {
	long long p, q;

	void reduce() {
		long long g = __gcd(p<0?-p:p, q<0?-q:q);
		p /= g;
		q /= g;
		if (q < 0) { q = -q; p = -p; }
	}

	Fraction(long long P, long long Q) : p(P), q(Q) { reduce(); }
};

void solve(char *s) {
	Fraction res(1, 1);

	while (*s) {
		if (!isdigit(*s)) { s++; continue; }

		char *t = s;
		while (isdigit(*s) || *s == '-' || *s == '/') s++;
		*s++ = 0;

		Fraction f(1, 1);
		if (strchr(t, '-') == NULL && strchr(t, '/') == NULL) {
			sscanf(t, "%lld", &f.p);
			f.q = 1;
		} else if (strchr(t, '-') == NULL) {
			if (sscanf(t, "%lld / %lld", &f.p, &f.q) < 1)
				f.q = 1;
		} else {
			long long a = 1;
			int b = sscanf(t, "%lld - %lld / %lld", &a, &f.p, &f.q);

			if (b == 1) { f.p = a; f.q = 0; }
			else if (b == 3) { f.p += f.q * a; }
		}

		res.p *= f.p;
		res.q *= f.q;
		res.reduce();
	}

	res.reduce();
	if ((res.p % res.q) == 0)
		printf("%lld\n", res.p / res.q);
	else if (res.p >= res.q)
		printf("%lld-%lld/%lld\n", res.p/res.q, res.p%res.q, res.q);
	else
		printf("%lld/%lld\n", res.p, res.q);
}

int main()
{
	char buf[65536];
	int T;

	gets(buf);
	sscanf(buf, "%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		gets(buf);
		solve(buf);
	}
}
