// DP
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

struct Order {
	int a, b, price;
	bool operator <(const Order &other) const {
		return a < other.a;
	}
};

int best[10010], N;
Order orders[10010];

int find(int t)
{
	int a = 0, b = N;
	while (b-a > 1) {
		int mid = (a + b) / 2;
		if (orders[mid].a >= t)
			b = mid;
		else
			a = mid;
	}
	return b;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%d %d %d", &orders[i].a, &orders[i].b, &orders[i].price);
		sort(orders, orders+N);

		best[N] = 0;
		for (int i = N-1; i >= 0; i--)
			best[i] = max(best[i+1],
						  best[find(orders[i].a + orders[i].b)] + orders[i].price);
		printf("%d\n", best[0]);
	}
}
