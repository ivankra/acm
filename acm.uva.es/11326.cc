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

double PI = 2*acos(0.0);

int main()
{
	int T;
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		int L, W, theta;
		scanf("%d %d %d", &L, &W, &theta);
		if (theta == 0) {
			printf("1.000\n");
			continue;
		}

		double sinT = sin(theta * PI / 180.0);
		double cosT = cos(theta * PI / 180.0);

		double hyp = W / sinT;
		double a = hyp * cosT;

		int n = (int)floor(L / a);
		double b = L - a * n;
		double y = b * sinT / cosT;

//printf("L=%d W=%d  theta=%d deg  sin=%.5f ", L,W,theta,sinT);
//printf("hyp=%.3f a=%.3f n=%d  b=%.3f y=%.3f\n",hyp,a,n,b,y);

		double ray = hyp * n + sqrt(y*y+b*b);

		if (n % 2 == 1) {
			y = W - y;
		}

		double straight = sqrt(L*L + y*y);

		printf("%.3f\n", ray / straight);
	}
}
