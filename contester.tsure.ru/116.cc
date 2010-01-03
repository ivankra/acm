#include <cstdio>
#include <algorithm>
using namespace std;

struct Point { long long x, y; } P[15010];

bool cmp(int ra, int rb) {
	Point &p = P[ra], &q = P[rb];
	return (p.x*q.y-p.y*q.x)<0;
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lld %lld",&P[i].x, &P[i].y);

	int s = 0;
	for (int i = 0; i < n; i++)
		if (P[i].x<P[s].x || (P[i].x==P[s].x && P[i].y<P[s].y)) s=i;

	int r[15010], m = 0;
	for (int i = 0; i < n; i++) {
		if (i == s) continue;
		r[m++] = i;
		P[i].x -= P[s].x;
		P[i].y -= P[s].y;
	}
	sort(r, r+m, cmp);

	printf("%d %d\n", s+1, r[(m-1)/2]+1);
}
