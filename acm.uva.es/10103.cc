#include <cstdio>
#include <cstring>
#include <cctype>
#include <cassert>
#include <algorithm>
#include <queue>
using namespace std;

int N, possible[128];

int dx[] = { 1, -1, 0, 0, 0, 0 };
int dy[] = { 0, 0, 1, -1, 0, 0 };
int dz[] = { 0, 0, 0, 0, 1, -1 };

struct Pos {
	int x, y, z;
	bool inside() const { return 0<=x&&x<N && 0<=y&&y<N && 0<=z&&z<N; }
};

struct Figure {
	Pos a[1001];
	int m, col;
	Pos &operator[](int i) { return a[i]; }
	const Pos &operator[](int i) const { return a[i]; }
	void operator +=(const Pos &p) { a[m++] = p; }
	bool out() const {
		for (int i = 0; i < m; i++)
			if (a[i].inside()) return false;
		return true;
	}
	void shift(int d) {
		for (int i = 0; i < m; i++) {
			a[i].x += dx[d];
			a[i].y += dy[d];
			a[i].z += dz[d];
		}
	}
	void shift(const Pos &p) {
		for (int i = 0; i < m; i++) {
			a[i].x += p.x;
			a[i].y += p.y;
			a[i].z += p.z;
		}
	}
};

bool isect(const Figure &A, const Figure &B) {
	static int f[64][64][64], id=0;
	if (id++ == 0) memset(f, 0, sizeof(f));
	for (int i = 0; i < A.m; i++)
		f[A[i].x+32][A[i].y+32][A[i].z+32] = id;
	for (int i = 0; i < B.m; i++)
		if (f[B[i].x+32][B[i].y+32][B[i].z+32] == id) return true;
	return false;
}

void doit2(Figure A0, Figure B) {
	static int seen[32][32][32];
	memset(seen, 0, sizeof(seen));

	queue<Pos> Q;
	Pos p = {0,0,0};
	Q.push(p);

	while (!Q.empty()) {
		p = Q.front(); Q.pop();
		seen[16+p.x][16+p.y][16+p.z] = 1;

		Figure A = A0;
		A.shift(p);
		if (A.out()) {
			possible[A0.col] = possible[B.col] = 1;
			return;
		}

		for (int d = 0; d < 6; d++) {
			Pos p1 = {p.x+dx[d], p.y+dy[d], p.z+dz[d] };
			int &tt = seen[16+p1.x][16+p1.y][16+p1.z];
			if (tt) continue;
			tt = 1;

			Figure AA = A;
			AA.shift(d);
			if (!isect(AA, B)) Q.push(p1);
		}
	}
}

void doit3(Figure A, Figure B, Figure C) {
	for (int d = 0; d < 6; d++) {
		Figure A1 = A;
		for (;;) {
			if (isect(A1, B) || isect(A1, C)) break;
			if (A1.out()) {
				possible[A1.col] = 1;
				doit2(B, C);
				break;
			}
			A1.shift(d);
		}
	}
}

int main()
{
	while (scanf("%d", &N) == 1 && N >= 1) {
		Figure R, G, B;
		R.m = G.m = B.m = 0;
		R.col = 'R';
		G.col = 'G';
		B.col = 'B';

		for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		for (int k = 0; k < N; k++) {
			int c;
			while ((c = getchar()) != EOF && !isalpha(c));

			Pos p = {i, j, k};
			if (c == 'R') R += p;
			else if (c == 'G') G += p;
			else if (c == 'B') B += p;
			else assert(0==1);
		}

		memset(possible, 0, sizeof(possible));

		doit3(R, G, B);
		doit3(G, R, B);
		doit3(B, G, R);

		int k = 0;
		for (int i = 0; i < 3; i++) {
			int c = "RGB"[i];
			if (possible[c]) { printf("%c", c); k++; }
		}
		printf(k ? "\n" : "NO\n");
	}
}
