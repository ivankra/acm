/*
ID: infnty1
PROB: transform
LANG: C++
*/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> VI; typedef vector<VI> VVI;

int n;

VVI rot(VVI &p) {
	VVI q = VVI(n, VI(n, 0));
	for (int r = 0; r < n; r++)
		for (int c = 0; c < n; c++)
			q[c][n-1-r] = p[r][c];
	return q;
}

VVI hrefl(VVI &p) {
	VVI q = VVI(n, VI(n, 0));
	for (int r = 0; r < n; r++)
		for (int c = 0; c < n; c++)
			q[r][n-1-c] = p[r][c];
	return q;
}

int solve(VVI p, VVI q) {
	int i;

	for (i = 0; i < 4; i++, p = rot(p))
		if (p == q && i > 0) return i;

	p = hrefl(p);
	for (i = 0; i < 4; i++, p = rot(p))
		if (p == q) return (i == 0 ? 4 : 5);
	p = hrefl(p);

	return (p == q) ? 6 : 7;
}

VVI readpat() {
	VVI p = VVI(n, VI(n, 0));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			int c;
			while ((c = getchar()) != EOF)
				if (c == '@' || c == '-') break;
			p[i][j] = c;
		}
	return p;
}

int main()
{
	freopen("transform.in", "r", stdin);
	freopen("transform.out", "w", stdout);

	scanf("%d", &n);
	VVI p = readpat();
	VVI q = readpat();

	printf("%d\n", solve(p, q));

	return 0;
}
