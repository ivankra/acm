#include <cstdio>
#include <algorithm>
using namespace std;

struct Board {
	char a[3][3];

	int encode() {
		int r = 0;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				r = r * 3 + a[i][j];
		return r;
	}

	bool complete() {
		int r = 0;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (a[i][j] != 0) r++;
		return r==9;
	}

	bool wins(int p) {
		for (int i = 0; i < 3; i++) {
			if (a[i][0]==p && a[i][1]==p && a[i][2]==p) return true;
			if (a[0][i]==p && a[1][i]==p && a[2][i]==p) return true;
		}
		if (a[0][0]==p && a[1][1]==p && a[2][2]==p) return true;
		return a[0][2]==p && a[1][1]==p && a[2][0]==p;
	}

	bool read() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3;) {
				int c = getchar();
				if (c == EOF) return false;
				else if (c == '.') a[i][j] = 0;
				else if (c == 'O') a[i][j] = 1;
				else if (c == 'X') a[i][j] = 2;
				else continue;
				j++;
			}
		}
		return true;
	}
};

int memo[20000][2];

int perfect(Board &b, int st) {
	int &ret = memo[b.encode()][st-1];
	if (ret != -1) return ret;

	int w1 = b.wins(1), w2 = b.wins(2);
	if (w1 && w2) return ret = 0;
	if (w1 || w2) return ret = (w1 ? 1 : 2);
	if (b.complete()) return ret = 0;

	ret = 3-st;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (b.a[i][j] != 0) continue;

			b.a[i][j] = st;
			int t = perfect(b, 3-st);
			b.a[i][j] = 0;

			if (t == st) return ret = st;
			if (t == 0) ret = 0;
		}
	}
	return ret;
}

int sc(int a, int b) {
	if (a == 0) return 0;
	if (a == b) return 1;
	return -1;
}

int main()
{
	Board b;
	int a[1024], n;
	memset(memo, 0xff, sizeof(memo));
	for (int cs = 1; scanf("%d", &n) == 1 && n >= 2; cs++) {
		int s = 0;
		for (int i = 0; i < n; i++) {
			if (!b.read()) return 0;
			int mary = sc(perfect(b, 1), 1);
			int john = sc(perfect(b, 2), 2);
			a[i] = mary + john;
			s -= john;
		}

		sort(a, a+n);
		for (int i = n-2; i >= 0; i -= 2)
			s += a[i];

		printf("Case %d: ", cs);
		if (s == 0)
			printf("Draw.\n");
		else if (s > 0)
			printf("Mary wins.\n");
		else
			printf("Johnny wins.\n");
	}
}
