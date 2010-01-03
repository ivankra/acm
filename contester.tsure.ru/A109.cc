#include <cstdio>
#include <algorithm>
using namespace std;

struct Point { long long x, y; } P[1024];

bool operator <(const Point &p, const Point &q) {
	return p.x<q.x || (p.x==q.x && p.y<q.y);
}

long long cross(const Point &o, const Point &a, const Point &b) {
	return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}

int main()
{
	int n, ret=0, in[1024], s[1024];

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lld %lld", &P[i].x, &P[i].y);
	sort(P, P+n);

	while (n > 2) {
		for (int i = 0; i < n; i++) in[i] = 0;

		int m = 0;
		for (int i = 0; i < n; i++) {
			while (m>=2 && cross(P[s[m-2]],P[s[m-1]],P[i])<0) m--;
			s[m++] = i;
		}
		for (int i = 0; i < m; i++) in[s[i]] = 1;

		m = 0;
		for (int i = n-1; i >= 0; i--) {
			while (m>=2 && cross(P[s[m-2]],P[s[m-1]],P[i])<0) m--;
			s[m++] = i;
		}
		for (int i = 0; i < m; i++) in[s[i]] = 1;

		m = 0;
		for (int i = 0; i < n; i++) {
			if (in[i]) continue;
			if (i != m) P[m] = P[i];
			m++;
		}
		n = m;
		ret++;
	}

	printf("%d %d\n", n, ret);
}
