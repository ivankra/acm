#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	int x, T;
	scanf("%d", &T);
	while (T-- > 0) {
		vector<int> v;
		while (scanf("%d", &x) == 1 && x > 0) v.push_back(x);

		sort(v.begin(), v.end());

		int k = 0;
		while (scanf("%d", &x) == 1 && x > 0)
			printf(k++ ? " %d" : "%d", v[x-1]);
		printf("\n");
	}
}
