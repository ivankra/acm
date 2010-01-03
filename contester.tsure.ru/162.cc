#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

double PI = 2.0 * acos(0.0);

struct Num {
	int x, y;

	Num(int X, int Y) : x(X), y(Y) {}

	double value() const { return x + PI * y; }

	bool operator ==(const Num &o) const { return x==o.x && y==o.y; }
	bool operator <(const Num &o) const { return !(*this == o) && value() < o.value(); }
	bool operator <=(const Num &o) const { return *this == o || *this < o; }

	Num operator +(const Num &o) const { return Num(x+o.x, y+o.y); }
	Num operator -(const Num &o) const { return Num(x-o.x, y-o.y); }
};

int main() {
	vector<Num> a;
	for (int x = 4; x <= 62; x++)
		for (int y = 0; y <= 22; y++)
			a.push_back(Num(x, y));
	sort(a.begin(), a.end());

	vector<int> b(a.size(), 0);
	b[0] = 1;

	for (int i = 1; i < (int)a.size(); i++) {
		b[i] = 0;
		for (int k = 0; k < 2; k++) {
			Num t = a[i] - Num(k, 1-k);

			int j = i-1;
			while (j > 0 && t <= a[j-1]) j--;
			b[i] += b[j];
		}

//		printf("P[%.5f, %.5f) => %d\n", a[i-1].value(), a[i].value(), b[i]);
	}

	int x;
	scanf("%d", &x);

	int i;
	for (i = 0; a[i] <= Num(x, 0); i++);

	printf("%d\n", b[i]);
}
