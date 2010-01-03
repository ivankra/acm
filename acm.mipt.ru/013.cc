#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

struct Cube {
	int x[3];

	bool in(const Cube &c) const {
		return x[0] < c.x[0] && x[1] < c.x[1] && x[2] < c.x[2];
	}

	void read() {
		scanf("%d %d %d", &x[0], &x[1], &x[2]);
		sort(x, x+3);
	}
};

Cube C[512];
int match[512], seen[512], N;

int dfs(int x) {
	if (seen[x]++) return 0;
	for (int y = 0; y < N; y++) {
		if (C[y].in(C[x]) && (match[y] < 0 || dfs(match[y]))) {
			match[y] = x;
			return 1;
		}
	}
	return 0;
}

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++) C[i].read();

	memset(match, 0xff, sizeof(match));

	int res = N;
	for (int x = 0; x < N; x++) {
		memset(seen, 0, sizeof(seen));
		if (dfs(x)) res--;
	}
	printf("%d\n", res);
}
