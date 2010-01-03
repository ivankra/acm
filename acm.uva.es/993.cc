// Greedy
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	int T, N;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		if (N <= 9) { printf("%d\n", N); continue; }

		int c[10];
		memset(c, 0, sizeof(c));
		while (N % 2 == 0) { N /= 2; c[2]++; }
		while (N % 3 == 0) { N /= 3; c[3]++; }
		while (N % 5 == 0) { N /= 5; c[5]++; }
		while (N % 7 == 0) { N /= 7; c[7]++; }
		if (N != 1) { printf("-1\n"); continue; }

		vector<int> v;
		while (c[5] >= 1) { c[5] -= 1; v.push_back(5); }
		while (c[7] >= 1) { c[7] -= 1; v.push_back(7); }
		while (c[2] >= 3) { c[2] -= 3; v.push_back(8); }
		while (c[3] >= 2) { c[3] -= 2; v.push_back(9); }

		if (c[3] == 1 && c[2] > 0) { c[3]--; c[2]--; v.push_back(6); }

		while (c[2] >= 2) { c[2] -= 2; v.push_back(4); }
		while (c[2] >= 1) { c[2] -= 1; v.push_back(2); }
		while (c[3] >= 1) { c[3] -= 1; v.push_back(3); }

		sort(v.begin(), v.end());
		for (int i = 0; i < (int)v.size(); i++)
			printf("%d", v[i]);
		printf("\n");
	}

	return 0;
}
