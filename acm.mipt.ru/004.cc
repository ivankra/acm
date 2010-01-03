#include <cstdio>
#include <algorithm>
using namespace std;

struct Athlete {
	int m, s;
	bool operator <(const Athlete &y) const { return s < y.s; }
};

int main()
{
	Athlete a[1024];
	int n;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &a[i].m, &a[i].s);

	sort(a, a+n);

	int w[1024], h=0;

	fill(w, w+n, 1<<30);
	w[0] = 0;

	for (int i = 0; i < n; i++) {
		if (w[h] <= a[i].s) {
			w[h+1] = w[h] + a[i].m;
			h++;
		}

		for (int j = h; j >= 0; j--)
			w[j+1] = min(w[j+1], w[j] + a[i].m);
	}

	printf("%d\n", h);
}
