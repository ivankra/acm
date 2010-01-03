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

// dI = kh d(alpha)

double X[300], Y[300];
int N;

double angularSpan()
{
	double maxAlpha = 0, minAlpha = 0, alpha = 0;
	for (int i = 0; i < N; i++) {
		double sign = (X[i+1]*Y[i] - X[i]*Y[i+1] > 0) ? +1 : -1;
		double t = X[i]*X[i+1] + Y[i]*Y[i+1];
		t /= sqrt(X[i]*X[i] + Y[i]*Y[i]);
		t /= sqrt(X[i+1]*X[i+1] + Y[i+1]*Y[i+1]);
		if (t < -1) t = -1;
		if (t > 1) t = 1;
		alpha += sign * acos(t);
		maxAlpha >?= alpha;
		minAlpha <?= alpha;
	}
	return min(maxAlpha - minAlpha, 4*acos(0.0));
}

int main()
{
	int T;
	cin >> T;

	for (int cs = 1; cs <= T; cs++) {
		double k, h;
		cin >> k >> h >> N;
		for (int i = 0; i < N; i++) {
			cin >> X[i] >> Y[i];
			X[N+i] = X[i];
			Y[N+i] = Y[i];
		}
		if (cs != 1) printf("\n");
		printf("%.2f\n", k*h*angularSpan());
	}
}
