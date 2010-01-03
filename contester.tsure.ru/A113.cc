#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

int main()
{
	int N, K, D[100];
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) scanf("%d", &D[i]);

	for (int i = 0; i < N; i++) {
		if (i > 0) printf(" ");
		printf("%d", (i == 0) ? K/D[0]-1 : D[i-1]/D[i]-1);
	}
	printf("\n");
}
