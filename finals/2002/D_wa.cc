#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <deque>
#include <set>
using namespace std;
typedef long long LL;

struct Seg {
	int isRoad, len;
	int departs[60];

	double minSpeed[60];
	int totalTime[60];
};

vector<Seg> S;

void solve()
{
	{
		Seg s;
		s.isRoad = 1;
		for (int i = 0; i < 60; i++) {
			s.minSpeed[i] = 0;
			s.totalTime[i] = 0;
			s.departs[i] = 1;
		}
		S.push_back(s);
	}

	for (int i = S.size()-2; i >= 0; --i) {
		for (int t0 = 0; t0 < 60; t0++) {
			if (S[i].isRoad) {
				if (i + 1 >= (int)S.size()-1) {
					S[i].minSpeed[t0] = 80;
					S[i].totalTime[t0] = 45 * S[i].len;
					continue;
				}

				int t1_ = (t0*60 + 45*S[i].len + 59) / 60;
				S[i].minSpeed[t0] = 1000000;
				S[i].totalTime[t0] = 1000000;
				for (int t1 = t1_; t1 <= t1_ + 600; t1++) {
					if (!S[i+1].departs[t1%60]) continue;

					double v = S[i].len * 60 / (double)(t1 - t0);
					v = max(v, S[i+1].minSpeed[t1%60]);

					int t = (t1 - t0) * 60 + S[i+1].totalTime[t1%60];
					if (t < S[i].totalTime[t0] ||
							(t == S[i].totalTime[t0] && v < S[i].minSpeed[t0])) {
						S[i].minSpeed[t0] = v;
						S[i].totalTime[t0] = t;
					}
				}
			} else {
				int t1 = t0 + S[i].len;                 // in minutes
				while (!S[i+1].departs[t1%60]) t1++;
				S[i].minSpeed[t0] = S[i+1].minSpeed[t1%60];
				S[i].totalTime[t0] = (t1 - t0)*60 + S[i+1].totalTime[t1%60];
			}
		}
	}

	int t = S[0].totalTime[0];
	printf("%.2d:%.2d:%.2d %.2f\n\n", t/3600, (t/60)%60, t%60, S[0].minSpeed[0]);
}

int main()
{
	int N, m, x;
	char kind[100];
	Seg s;

	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		printf("Test Case %d: ", cs);

		S.clear();
		for (int i = 0; i < N; i++) {
			scanf(" %*s %*s %s", kind);
			if (kind[0] == 'r') {
				s.isRoad = 1;
				scanf("%d", &s.len);
				if (S.size() > 0 && S.back().isRoad)
					S.back().len += s.len;
				else
					S.push_back(s);
			} else {
				s.isRoad = 0;
				scanf("%d %d", &s.len, &m);
				memset(s.departs, 0, sizeof(s.departs));
				for (int j = 0; j < m; j++) {
					scanf("%d", &x);
					s.departs[x%60] = 1;
				}
				S.push_back(s);
			}
		}

		solve();
	}
}
