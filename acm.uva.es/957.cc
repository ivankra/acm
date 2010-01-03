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
#include <queue>
using namespace std;

int main()
{
	int x, N, Y;
	while (scanf("%d %d", &Y, &N) == 2 && Y > 0) {
		queue<int> Q;
		int best[3] = { -1, -1, -1 };

		for (int i = 0; i < N; i++) {
			scanf("%d", &x);
			Q.push(x);
			while (Q.size() > 0 && Q.back() - Q.front() >= Y)
				Q.pop();
			if ((int)Q.size() > best[0]) {
				best[0] = Q.size();
				best[1] = Q.front();
				best[2] = Q.back();
			}
		}

		printf("%d %d %d\n", best[0], best[1], best[2]);
	}
}
