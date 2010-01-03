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
using namespace std;

/*
 *  pi = 6 arcsin(1/2)
 *
 *  arcsin(x) = x + 1/2 (x^3/3) + (1/2)(3/4)(x^5/5) + 
 *              (1/2)(3/4)(5/6)(x^7/7) + ... 
 */

double term[1000001];

int main()
{
	term[0] = log10(3.0);
	for (int n = 0; n < 1000000; n++) {
		double z = 2*log10(2*n+1.) - log10(2*n+2.) - log10(2*n+3.) - log10(4.0);
		term[n+1] = term[n] + z;
	}

	int n;
	while (scanf("%d", &n) == 1 && n > 0) {
		int left = 0, right = 1000000;
		while (right - left > 1) {
			int m = (left + right) / 2;
			if (term[m] > -n)
				left = m;
			else
				right = m;
		}
		printf("%d\n", right);
	}
}
