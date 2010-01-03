#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

char s[50000];
int ptr, result, maxDepth;

void rec1(int depth)
{
	if (depth > maxDepth)
		maxDepth = depth;

	if (s[ptr++] == '1') {
		rec1(depth + 1);
		rec1(depth + 1);
	}
}

void rec2(int depth)
{
	if (depth == maxDepth) throw "Done";

	if (s[ptr++] == '1') {
		result++;
		rec2(depth + 1);
		rec2(depth + 1);
	}
}

int main()
{
	int n;
	for (int cs = 1; cs <= 10 && scanf("%d %s", &n, s) == 2; cs++) {
		maxDepth = 0;
		ptr = 0;
		rec1(0);

		result = 0;
		ptr = 0;
		try { rec2(0); } catch (...) { }

		printf("%d\n", result);
	}
}
