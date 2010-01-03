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

int X[100], Y[100], N;
int width, height;
bool seen[100];
double diameter;

bool dfs(int i)
{
	if (height - Y[i] < diameter) {
		return true;
	}

	if (seen[i]) return false;
	seen[i] = true;

	for (int j = 0; j < N; j++) {
		double dx = X[i] - X[j];
		double dy = Y[i] - Y[j];
		if (dx*dx + dy*dy < diameter*diameter && dfs(j))
			return true;
	}

	return false;
}

bool possible()
{
	memset(seen, 0, sizeof(seen));
	for (int i = 0; i < N; i++) {
		if (Y[i] < diameter && dfs(i))
			return false;
	}
	return true;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d %d", &width, &height, &N);
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &X[i], &Y[i]);
		}

		double left = 0, right = height;
		while (right - left > 1e-6) {
			double middle = (left + right) / 2;
			diameter = middle;
			if (possible())
				left = middle;
			else
				right = middle;
		}
		printf("Maximum size in test case %d is %.4f.\n", cs, left);
	}
}
