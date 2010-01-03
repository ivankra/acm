#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
using namespace std;
typedef pair<int, int> P;

bool cmp(const P &a, const P &b) {
	return a.first*(long long)b.second > a.second*(long long)b.first;
}

int main()
{
	int N;
	while (scanf("%d", &N) == 1 && N != 0) {
		int sumx = 0, sumy = 0;
		vector<P> v;
		for (int ss = 1; sumx+sumy+ss <= N; ss++) {
			for (int a = 1; a < ss; a++) {
				int b = ss-a;
				if (__gcd(a, b) != 1) continue;
				v.push_back(P(a, b));
				sumx += a;
				sumy += b;
				if (sumx+sumy+ss > N) break;
			}
		}
		sort(v.begin(), v.end(), cmp);
		if (sumx+sumy < N) {
			v.insert(v.begin(), P(N-sumx-sumy, 0));
			sumx += N-sumx-sumy;
		}

		int curX = sumy, curY = 0;
		printf("(%d,%d)\n", curX, curY);
		for (int k = 0; k < 4; k++) {
			for (int i = 0; i < (int)v.size(); i++) {
				int dx = v[i].first, dy = v[i].second;
				for (int j = 0; j < k; j++) {
					swap(dx, dy);
					dx = -dx;
				}
				curX += dx; curY += dy;
				if (k == 3 && i == (int)v.size()-1) continue;
				printf("(%d,%d)\n", curX, curY);
				assert(0 <= curX && curX <= N);
				assert(0 <= curY && curY <= N);
			}
		}
		printf("\n");
		//fprintf(stderr, "<%d>\n", v.size()*4);
	}
}
