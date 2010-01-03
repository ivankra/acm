/*
ID: infnty1
LANG: C++
TASK: alake
*/
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define MAXN 100010

int N, width[MAXN], height[MAXN], prev[MAXN], next[MAXN], cur;
long long ans[MAXN], curTime;

int main()
{
	freopen("alake.in", "r", stdin);
	freopen("alake.out", "w", stdout);

	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &width[i], &height[i]);
		prev[i] = i-1;
		next[i] = i == N ? 0 : (i+1);
	}

	cur = 1;
	for (int i = 1; i <= N; i++) {
		if (height[i] < cur) cur = i;
		ans[i] = -1;
	}

	height[0] = 0x3fffffff;
	curTime = 0;

	while (true) {
		if (prev[cur] == 0 && next[cur] == 0) {
			ans[cur] = curTime + width[cur];
			break;
		}

		if (height[prev[cur]] < height[next[cur]]) {
			while (height[prev[cur]] < height[cur])
				cur = prev[cur];
		} else {
			while (height[next[cur]] < height[cur])
				cur = next[cur];
		}
		ans[cur] = curTime + width[cur];

		assert(height[prev[cur]] > height[cur]);
		assert(height[next[cur]] > height[cur]);
		assert(height[prev[cur]] != height[next[cur]]);

		if (height[prev[cur]] < height[next[cur]]) {
			curTime += width[cur] * (long long)(height[prev[cur]] - height[cur]);
			width[prev[cur]] += width[cur];
			next[prev[cur]] = next[cur];
			prev[next[cur]] = prev[cur];
			cur = prev[cur];
		} else {
			curTime += width[cur] * (long long)(height[next[cur]] - height[cur]);
			width[next[cur]] += width[cur];
			next[prev[cur]] = next[cur];
			prev[next[cur]] = prev[cur];
			cur = next[cur];
		}
	}

	for (int i = 1; i <= N; i++) {
		printf("%lld\n", ans[i]);
	}
}

