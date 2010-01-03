#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <cmath>
#include <cassert>
#include <map>
using namespace std;
typedef vector<int> VI;

double EPS = 1e-8;
int DY[]={1,-1,0,0}, DX[]={0,0,1,-1};
int nrows, ncols, faucetR, faucetC;
double cell[20][20];

struct Zone {
	int id, area;
	VI out;
	double inrate, level, maxLevel;
};

bool cmp(Zone *a, Zone *b) { return a->level > b->level; }

vector<Zone *> zones;
Zone *zoneAt[20][20];

int inside(int r, int c) {
	return 1 <= r && r <= nrows && 1 <= c && c <= ncols;
}

Zone *do_zone(int r0, int c0);

void dfs(Zone *z, int r, int c)
{
	if (zoneAt[r][c] != NULL) return;
	zoneAt[r][c] = z;

	z->area++;

	for (int i = 0; i < 4; i++) {
		int rr = r + DY[i], cc = c + DX[i];
		if (!inside(rr, cc)) continue;

		if (fabs(cell[rr][cc] - z->level) < EPS) {
			dfs(z, rr, cc);
		} else if (cell[rr][cc] < z->level) {
			z->out.push_back(do_zone(rr, cc)->id);
		} else {
			z->maxLevel = min(z->maxLevel, cell[rr][cc]);
		}
	}
}

Zone *do_zone(int r0, int c0)
{
	if (zoneAt[r0][c0] == NULL) {
		zones.push_back(new Zone());
		Zone *z = zones.back();
		z->level = cell[r0][c0];
		z->inrate = 0;
		z->out.clear();
		z->id = zones.size() - 1;
		z->maxLevel = 10;
		z->area = 0;
		dfs(z, r0, c0);
	}
	return zoneAt[r0][c0];
}

int main()
{
	int i, j;
	while (cin >> nrows >> ncols >> faucetR >> faucetC) {
		if (nrows == 0 && ncols == 0) break;

		for (i = 1; i <= nrows; i++)
			for (j = 1; j <= ncols; j++)
				cin >> cell[i][j];

		double res = 0;

		while (true) {
			for (i = 0; i < (int)zones.size(); i++) delete zones[i];
			zones.clear();
			memset(zoneAt, 0, sizeof(zoneAt));
			do_zone(faucetR, faucetC);

			bool done = false;
			for (i = 1; i <= nrows; i++)
				for (j = 1; j <= ncols; j++)
					if (i == 1 || i == nrows || j == 1 || j == ncols)
						if (zoneAt[i][j] != NULL)
							done = true;
			if (done) break;

			vector<Zone *> zzz = zones;
			sort(zzz.begin(), zzz.end(), cmp);

			double delta = 1e99;
			zones[0]->inrate = 1;

			for (i = 0; i < (int)zzz.size(); i++) {
				Zone *z = zzz[i];
				if (z->out.size() != 0) {
					for (j = 0; j < (int)z->out.size(); j++) {
						Zone *w = zones[z->out[j]];
						w->inrate += z->inrate / z->out.size();
					}
				} else {
					delta = min(delta, (z->maxLevel - z->level) / z->inrate * z->area);
				}
			}

			res += delta;
			for (i = 0; i < (int)zones.size(); i++) {
				Zone *z = zones[i];
				if (z->out.size() == 0) {
					z->level += delta * z->inrate / z->area;
				}
			}

			for (i = 1; i <= nrows; i++) {
				for (j = 1; j <= ncols; j++) {
					if (zoneAt[i][j] != NULL)
						cell[i][j] = zoneAt[i][j]->level;
				}
			}
		}

		printf("%.2f\n", res);
	}
}
