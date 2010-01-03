#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	int T, N;
	scanf("%d", &T);
	for (int cs = 1; cs <= T && scanf("%d", &N) == 1; cs++) {
		double p = 1;
		for (int k = N/2+1; k <= N; k++)
			p -= 1.0 / k;
		printf("Case #%d: %.8f %.8f\n", cs, p, 1.0/p);
	}
}
