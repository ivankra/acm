#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int row[65536];

void mkrow()
{
	for (int i = 1, r = 1; i < 65536; r++)
		for (int j = 0; j < r && i < 65536; j++, i++)
			row[i] = r;
}

int dist(int v1, int v2)
{
	if (v1 > v2) swap(v1, v2);

	int r1 = row[v1], c1 = v1 - (r1-1)*r1/2;
	int r2 = row[v2], c2 = v2 - (r2-1)*r2/2;

	if (r1 == r2) return c2 - c1;
	if (c1 == c2) return r2 - r1;
	if (c2 == c1 + r2 - r1) return r2 - r1;

	return -1;
}

int chk(vector<int> &v)
{
	for (int i = 0, m = 0; i < v.size(); i++) {
		int d = dist(v[i], v[(i+1) % v.size()]);
		if (d <= 0 || (i > 0 && d != m)) return 0;
		m = d;
	}
	return 1;
}

char *solve(vector<int> &v)
{
	if (v.size() == 3 || v.size() == 4 || v.size() == 6) {
		sort(v.begin(), v.end());
		do {
			if (chk(v)) {
				if (v.size() == 3)
					return "the vertices of a triangle";
				else if (v.size() == 4)
				 	return "the vertices of a parallelogram";
				else
				 	return "the vertices of a hexagon";
			}
		} while (next_permutation(v.begin(), v.end()));
	}
	return "not the vertices of an acceptable figure";
}

int main()
{
	static char buf[65536];
	vector<int> v;
	int x, p, q;

	mkrow();

	while (gets(buf)) {
		for (v.clear(), p=0; sscanf(buf+p, " %d %n", &x, &q) >= 1; p+=q)
			v.push_back(x);

		for (int i = 0; i < v.size(); i++)
			printf("%d ", v[i]);

		printf("are %s\n", solve(v));
	}

	return 0;
}
