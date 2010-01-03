#include <cstdio>
#include <vector>
using namespace std;

vector<int> v[32];
int x;

int go(int k)
{
	int i, r = ++x;
	v[k-1].push_back(r);
	for (i = 1; i < k; i++)
		printf("%d %d\n", r, go(i));
	return r;
}

int main()
{
	int i, k;

	while (scanf("%d", &k) == 1) {
		printf("%d %d\n", 1 << (k-1), (1 << (k-1)) - 1);

		x = 0;
		go(k);

		for (i = x = 0; i < k; i++)
			for (; !v[i].empty(); v[i].pop_back())
				printf(x++ ? " %d" : "%d", v[i].back());
		printf("\n");
	}

	return 0;
}
