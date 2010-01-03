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
	int N;
	int a[128][128];

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &a[i][j]);

	for (int k = 0; k < N+N; k++)
		for (int i = N-1; i >= 0; i--)
			for (int j = N-1; j >= 0; j--)
				if (i+j == k) printf(k==0 ? "%d" : " %d", a[i][j]);

	printf("\n");
}
