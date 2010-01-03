#include <stdio.h>
#include <map>

using namespace std;

map<pair<int, int>, int> m;

int f(int a, int b)
{
	int t;

	if (a > b)
		t = a, a = b, b = t;

	if (a == 0)
		return 1;

	if (m.count(pair<int,int>(a, b)) > 0)
		return m[pair<int,int>(a, b)];

	if ((b % a) == 0) {
		m[pair<int,int>(a, b)] = 1;
		return 1;
	}

	t = b / a;
	t = b - ((t > 2) ? (t - 2) : 1) * a;

	for (; t >= 0; t -= a)
		if (f(a, t) == 0) {
			m[pair<int,int>(a, b)] = 1;
			return 1;
		}

	m[pair<int,int>(a, b)] = 0;
	return 0;
}

int main()
{
	int a, b;

	while (scanf("%d %d", &a, &b) == 2 && (a != 0 || b != 0)) {
		m.clear();
		printf(f(a, b) ? "Stan wins\n" : "Ollie wins\n");
	}

	return 0;
}
