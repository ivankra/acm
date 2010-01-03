#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

int A[10];
double AA[10];

struct Rec {
	double y;
	int x[3];
	bool operator <(const Rec &b) const { return y < b.y; }
};

int solve() {
	for (int i = 1; i <= 6; i++)
		AA[i] = sqrt(A[i]+0.0);

	Rec r;
	static Rec v[10000];
	int vn = 0;

	for (r.x[0] = -9; r.x[0] <= 9; r.x[0]++) {
		for (r.x[1] = -9; r.x[1] <= 9; r.x[1]++) {
			for (r.x[2] = -9; r.x[2] <= 9; r.x[2]++) {
				r.y = AA[4]*r.x[0] + AA[5]*r.x[1] + AA[6]*r.x[2];
				v[vn++] = r;
			}
		}
	}
	sort(v, v+vn);

	int x[10];
	for (x[0] = -9; x[0] <= 9; x[0]++)
	for (x[1] = -9; x[1] <= 9; x[1]++)
	for (x[2] = -9; x[2] <= 9; x[2]++)
	for (x[3] = -9; x[3] <= 9; x[3]++) {
		double y0 = (x[0] + AA[1]*x[1] + AA[2]*x[2] + AA[3]*x[3]);

		int left = 0, right = vn-1;
		while (right-left > 2) {
			int mid = (left + right) / 2;
			if (v[mid].y > -y0) right = mid; else left = mid;
		}

		left = max(0, left-2);
		right = min(vn-1, right+2);

		for (int i = left; i <= right; i++) {
			if (fabs(y0 + v[i].y) < 1e-4) {
				if ((abs(x[0]) + abs(x[1]) + abs(x[2]) + abs(x[3]) +
				     abs(v[i].x[0]) + abs(v[i].x[1]) + abs(v[i].x[2])) == 0)
					continue;

				printf("%d %d %d %d %d %d %d\n",
					x[0], x[1], x[2], x[3],
					v[i].x[0], v[i].x[1], v[i].x[2]);
				return true;
			}
		}
	}

	return false;
}

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		for (int i = 1; i <= 6; i++) scanf("%d", &A[i]);

		printf("Case %d: ", cs);

		if (!solve())
			printf("No Solution.\n");
	}
}
