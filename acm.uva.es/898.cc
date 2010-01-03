// compress coordinates, do a few DFSs on the reduced board
// same as UVa 308
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

char plate[256][256];
int height, width;
int cutLeft[256][256], cutUp[256][256];

void externalDfs(int y, int x) {
	if (y <= 0 || x <= 0 || y > height || x > width) return;
	if (plate[y][x] != 0) return;
	plate[y][x] = 1;
	if (!cutUp[y][x]) externalDfs(y-1, x);
	if (!cutUp[y+1][x]) externalDfs(y+1, x);
	if (!cutLeft[y][x]) externalDfs(y, x-1);
	if (!cutLeft[y][x+1]) externalDfs(y, x+1);
}

void internalDfs(int y, int x) {
	if (y <= 0 || x <= 0 || y > height || x > width) return;
	if (plate[y][x] != 0) return;
	plate[y][x] = 1;
	internalDfs(y-1, x);
	internalDfs(y+1, x);
	internalDfs(y, x-1);
	internalDfs(y, x+1);
}

int main()
{
	int N;
	int x1[100], y1[100], x2[100], y2[100];

	while (scanf("%d", &N) == 1 && N > 0) {
		assert(N <= 100);

		vector<int> X, Y;
		for (int i = 0; i < N; i++) {
			scanf("%d %d %d %d", &x1[i], &y1[i], &x2[i], &y2[i]);
			X.push_back(x1[i]);
			X.push_back(x2[i]);
			Y.push_back(y1[i]);
			Y.push_back(y2[i]);
		}

		sort(X.begin(), X.end());
		X.erase(unique(X.begin(), X.end()), X.end());

		sort(Y.begin(), Y.end());
		Y.erase(unique(Y.begin(), Y.end()), Y.end());

		for (int i = 0; i < N; i++) {
			x1[i] = lower_bound(X.begin(), X.end(), x1[i]) - X.begin() + 5;
			x2[i] = lower_bound(X.begin(), X.end(), x2[i]) - X.begin() + 5;
			y1[i] = lower_bound(Y.begin(), Y.end(), y1[i]) - Y.begin() + 5;
			y2[i] = lower_bound(Y.begin(), Y.end(), y2[i]) - Y.begin() + 5;
		}

		memset(cutUp, 0, sizeof(cutUp));
		memset(cutLeft, 0, sizeof(cutLeft));

		for (int i = 0; i < N; i++) {
			if (x1[i] == x2[i]) {	// vertical cut
				int x = x1[i];
				int yLow = min(y1[i], y2[i]);
				int yHigh = max(y1[i], y2[i]);
				for (int y = yLow; y < yHigh; y++) {
					cutLeft[y][x] = 1;
				}
			} else if (y1[i] == y2[i]) {
				int y = y1[i];
				int xLow = min(x1[i], x2[i]);
				int xHigh = max(x1[i], x2[i]);
				for (int x = xLow; x < xHigh; x++) {
					cutUp[y][x] = 1;
				}
			} else {
				abort();
			}
		}

		memset(plate, 0, sizeof(plate));
		height = Y.size() + 10;
		width = X.size() + 10;
		externalDfs(1, 1);

		int n = 0;
		for (int y = 1; y <= height; y++) {
			for (int x = 1; x <= width; x++) {
				if (plate[y][x] == 0) {
					internalDfs(y, x);
					n++;
				}
			}
		}
		printf("%d\n", n);
	}
}
