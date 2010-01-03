// ICPC Finals 2003 - Problem C - Riding the Bus
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

double sqr(double x) { return x * x; }

int qx, qy, qdist;

int curve(int k, int &x, int &y, int dx, int dy)
{
	if (k == 0) {
//printf("(%d,%d)\n",x,y);
		return x == qx && y == qy;
	}

	if (!(min(x,x+dx) <= qx && qx <= max(x,x+dx) &&
		  min(y,y+dy) <= qy && qy <= max(y,y+dy))) {
		int z = 1;
		for (int i = 0; i < k; i++)
			z *= 9;
		qdist += z - 1;
		x += dx;
		y += dy;
		return 0;
	}

	int h = (abs(dx) - 2) / 3;
	int sx = dx > 0 ? 1 : -1;
	int sy = dy > 0 ? 1 : -1;

	if (curve(k-1, x, y, sx*h, sy*h)) return 1;
	x += sx; ++qdist;
	if (curve(k-1, x, y, sx*h, -sy*h)) return 1;
	x += sx; ++qdist;
	if (curve(k-1, x, y, sx*h, sy*h)) return 1;
	  y += sy; ++qdist;
	if (curve(k-1, x, y, -sx*h, sy*h)) return 1;
	x -= sx; ++qdist;
	if (curve(k-1, x, y, -sx*h, -sy*h)) return 1;
	x -= sx; ++qdist;
	if (curve(k-1, x, y, -sx*h, sy*h)) return 1;
	  y += sy; ++qdist;
	if (curve(k-1, x, y, sx*h, sy*h)) return 1;
	x += sx; ++qdist;
	if (curve(k-1, x, y, sx*h, -sy*h)) return 1;
	x += sx; ++qdist;
	if (curve(k-1, x, y, sx*h, sy*h)) return 1;

	return 0;
}

int curveOrder;
double px[2], py[2];
int ix[2], iy[2];

double solve()
{
	int m = 2;
	for (int i = 0; i < curveOrder-1; i++)
		m = m * 3 + 2;

	double len = 1.0 / m;
	double res = 0;

	for (int i = 0; i < 2; i++) {
		int xx = (int)floor(px[i] * m + 0.5 - 1e-9);
		xx = max(xx, 0); xx = min(xx, m);

		int yy = (int)floor(py[i] * m + 0.5 - 1e-9);
		yy = max(yy, 0); yy = min(yy, m);

		ix[i] = xx;
		iy[i] = yy;
		res += sqrt(sqr(ix[i]*len - px[i]) + sqr(iy[i]*len - py[i]));

//printf("%.5f,%.5f -> %d/%d, %d/%d = %.5f,%.5f\n",px[i], py[i], ix[i],m, iy[i],m, ix[i]/(m+0.0), iy[i]/(m+0.0));
	}

	int dist1, dist2;
	int tx, ty;

	qx = ix[0]; qy = iy[0]; tx = 0; ty = 0; qdist = 0;
	curve(curveOrder, tx, ty, m, m);
	dist1 = qdist;

	qx = ix[1]; qy = iy[1]; tx = 0; ty = 0; qdist = 0;
	curve(curveOrder, tx, ty, m, m);
	dist2 = qdist;

//printf("dist1=%d dist2=%d  delta=%d\n", dist1, dist2, dist2-dist1);

	res += fabs(dist1 - dist2 + 0.0) * len;
	return res;
}

int main()
{
	for (int cs = 1; scanf("%d", &curveOrder) == 1 && curveOrder > 0; cs++) {
		scanf("%lf %lf %lf %lf", &px[0], &py[0], &px[1], &py[1]);
		if (cs > 1) printf("\n");
		printf("Case %d.  Distance is %.4f\n", cs, solve());
	}
}
