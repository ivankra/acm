#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

long double PI = 2*acos(0.0L);

bool solve(int A, int B, int a, int b)
{
	if (A < B) swap(A, B);
	if (a < b) swap(a, b);
	if (a == b) return a < A && b < B;
	if (a < A && b < B) return true;
	if (a < B && b < A) return true;

	long double u = atan(b / (long double)a);
	long double v = atan(a / (long double)b);
	long double eps = 1e-5;

	for (int k = 0; k < 1024; k++) {
		long double c = k / 1024.0;
		long double alpha = u*(1-c) + v*c;
		long double x = a * sin(alpha) + b * cos(alpha);
		long double y = a * cos(alpha) + b * sin(alpha);
		if (x < A - eps && y < B - eps) {
			return true;
		}
	}

	return false;
}

int main() {
	int T, A, B, a, b;
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d %d %d", &A, &B, &a, &b);
		printf(solve(A, B, a, b) ? "Escape is possible.\n" : "Box cannot be dropped.\n");
	}
}
