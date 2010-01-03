#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;
typedef long long LL;
typedef long double LD;

LL sqr(LL z) { return z*z; }

bool cmp(const vector<LD> &a, const vector<LD> &b)
{
	for (int i = 0; i < 5; i++)
		if (fabs(a[i] - b[i]) > 1e-6)
			return a[i] < b[i];
	return false;
}

void solve(LL x1, LL y1, LL r1, LL x2, LL y2, LL r2)
{
	LL d_sq = sqr(x1 - x2) + sqr(y1 - y2);
	if (d_sq == 0) { printf("%d\n", r1 == r2 ? -1 : 0); return; }
	if (d_sq < sqr(r1 - r2)) { printf("0\n"); return; }

	LD d = sqrt((LD)d_sq);
	LD vx = (x2 - x1) / d;
	LD vy = (y2 - y1) / d;

	vector<vector<LD> > res;

	for (int s = -1; s <= 1; s += 2) {
		LL delta = r1 + s * r2;
		if (sqr(delta) > d_sq) continue;

		LD c = delta / (LD)d;
		LD h = sqrt(max(0.0L, 1.0L - c*c));

		for (int t = -1; t <= 1; t += 2) {
			LD nx = vx*c + t*h*(-vy);
			LD ny = vy*c + t*h*(vx);

			LD a[5];
			a[0] = x1 + nx*r1;
			a[1] = y1 + ny*r1;
			a[2] = x2 - s*nx*r2;
			a[3] = y2 - s*ny*r2;
			a[4] = sqrt((a[0]-a[2])*(a[0]-a[2]) + (a[1]-a[3])*(a[1]-a[3]));
			res.push_back(vector<LD>(a, a+5));

			if (sqr(delta) == d_sq) break;
		}
	}

	sort(res.begin(), res.end(), cmp);

	printf("%d\n", res.size());
	for (int i = 0; i < (int)res.size(); i++) {
		for (int j = 0; j < 5; j++) {
			char s[100];
			sprintf(s, "%.5Lf", res[i][j]);
			if (strcmp(s, "-0.00000") == 0) strcpy(s, "0.00000");
			printf(j == 4 ? "%s\n" : "%s ", s);
		}
	}
}

int main()
{
	int x1,y1,r1,x2,y2,r2;
	while (scanf("%d%d%d%d%d%d", &x1, &y1, &r1, &x2, &y2, &r2) == 6 && r1 > 0 && r2 > 0)
		solve(x1,y1,r1,x2,y2,r2);
}
