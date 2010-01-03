#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <ctime>
using namespace std;

int value[110000], N, mod;
int flag[110000];

int seen[110000], seen_at[110000], seen_id;

int solve()
{
	for (int i = 0; i < mod; i++) seen[i] = 0;

	seen[0] = 1;
	seen_at[0] = -1;

	int sum = 0;
	for (int i = 0; i < N; i++) {
		sum += value[i];
		sum %= mod;
		if (seen[sum]) {
			for (int j = seen_at[sum]+1; j <= i; j++)
				printf("%d%s", j+1, j==i ? "\n" : " ");
			return 1;
		}
		seen[sum] = 1;
		seen_at[sum] = i;
	}

	return 0;
}

int main()
{
	memset(seen, 0, sizeof(seen));
	seen_id = 42;

	srand(time(NULL));
	while (scanf("%d %d", &mod, &N) == 2 && mod > 0) {
		for (int i = 0; i < N; i++) scanf("%d", &value[i]);
		if (!solve()) printf("no sweets\n");
	}

	return 0;
}
