#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

int mat[1024][1024], N, M;

int main()
{
	for (int cs = 1; scanf("%d %d", &N, &M) == 2; cs++) {
		for (int i = 1; i <= N; i++) {
			int sum = 0;
			for (int j = 1; j <= N; j++) {
				scanf("%d", &mat[i][j]);
				sum += mat[i][j];
				mat[i][j] = mat[i-1][j] + sum;
			}
		}

		if (cs != 1) printf("\n");
		long long total = 0;
		for (int i = 0; i < N-M+1; i++) {
			for (int j = 0; j < N-M+1; j++) {
				int x = mat[i+M][j+M] - mat[i+M][j] - mat[i][j+M] + mat[i][j];
				printf("%d\n", x);
				total += x;
			}
		}
		printf("%lld\n", total);
	}
}
