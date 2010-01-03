#include <algorithm>
#include <vector>
#include <cstdio>
#include <cassert>
using namespace std;

struct Point {
	int x, y;
	Point(int X=0, int Y=0) : x(X), y(Y) {}
};

// Finds winding number of polygon Q around point P.
// Returns -1 if P lies on the boundary of polygon Q, else returns
// absolute value of winding number.
int winding_number(const Point &P, const vector<Point> &Q) {
	int r = 0, n = Q.size();
	for (int i = 0; i < n; i++) {
		const Point &A = Q[i], &B = Q[(i+1)<n?i+1:0];
		if (A.x == P.x && A.y == P.y) return -1;
		if (A.x == B.x && A.y == B.y) continue;

		if (A.y == P.y && B.y == P.y)
			if (min(A.x, B.x) <= P.x && P.x <= max(A.x, B.x)) return -1;

		if (A.y <= P.y && B.y <= P.y) continue;
		if (A.y > P.y && B.y > P.y) continue;

		long long det = (A.x-P.x)*(B.y-P.y)-(A.y-P.y)*(B.x-P.x);
		if (det == 0) return -1;

		r += (det < 0) ? -1 : 1;
	}
	if (r < 0) r = -r;
	assert((r & 1) == 0);
	return r/2;
}


#include <cctype>
int main() {
	char img[128][128];

	memset(img, ' ', sizeof(img));
	for (int i = 0; i < 128; i++) {
		int c;
		for (int j = 0; (c = getchar()) != EOF && c != '\n'; j++) {
			if (c == '\r') continue;
			img[i][j] = c;
		}
		if (c == EOF) break;
	}

	vector<Point> P;
	for (int c = 'A'; c <= 'Z'; c++) {
		for (int y = 0; y < 128; y++)
		for (int x = 0; x < 128; x++)
			if (img[y][x] == c) { P.push_back(Point(x,y)); goto done; }
		break;
done:;
	}

	for (int y = 0; y < 128; y++) {
		for (int x = 0; x < 128; x++) {
			int w = winding_number(Point(x, y), P);
			if (w < 0)
				img[y][x] = isalpha(img[y][x]) ? img[y][x] : '#';
			else if (w == 0)
				img[y][x] = ' ';
			else
				img[y][x] = '0' + w;
			putchar(img[y][x]);
		}
		printf("\n");
	}
}
