/*
ID: infnty1
TASK: corral
LANG: C++
*/
/* Binary search on length of side + O(N^2) scan to find largest number of
   fields in an SxS square for a fixed S. */
#include <cstdio>
#include <algorithm>
using namespace std;

struct pt { int x, y; };

bool cmpx(pt a, pt b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }
bool cmpy(pt a, pt b) { return a.y < b.y || (a.y == b.y && a.x < b.x); }

pt P[512], Py[512];
int in[512], S, C, N;

int check_s()
{
	int best=0, i, k, a, b;

	for (i = N-1; i >= 0; i--) {
		if (i < N-1 && Py[i+1].y == Py[i].y) continue;

		int Ly = Py[i].y;

		memset(in, 0, sizeof(in));
		for (a = b = k = 0; b < N; b++) {
			if (P[b].y < Ly || P[b].y >= Ly+S) continue;

			int Rx = P[b].x + 1, Lx = Rx - S;

			in[b] = 1;
			k++;

			while (a < b && P[a].x < Lx)
				k -= in[a++];

			best >?= k;
		}
	}

	return best;
}

int main()
{
	freopen("corral.in", "r", stdin);
	freopen("corral.out", "w", stdout);

	scanf("%d %d", &C, &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &P[i].x, &P[i].y);
		Py[i] = P[i];
	}

	sort(P, P+N, &cmpx);
	sort(Py, Py+N, &cmpy);

	int a=1, b=12000, k;
	while (a < b) {
		S = (a + b) / 2;
		if (check_s() >= C) b = S; else a = S + 1;
	}

	printf("%d\n", b);

	return 0;
}
