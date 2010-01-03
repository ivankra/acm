/*
ID: infnty1
PROB: subset
LANG: C++
*/
#include <cstdio>
#include <cstring>

int main() {
	freopen("subset.in", "r", stdin);
	freopen("subset.out", "w", stdout);

	int N;
	scanf("%d", &N);

	int sum = N*(N+1)/2;
	if (sum % 2 != 0) {
		printf("0\n");
		return 0;
	}

	long long ways[1000];
	memset(ways, 0, sizeof(ways));
	ways[0] = 1;

	for (int i = 1; i <= N; i++)
		for (int s = i*(i+1)/2; s >= i; s--)
			ways[s] += ways[s-i];

	printf("%lld\n", ways[sum/2]/2);
}
