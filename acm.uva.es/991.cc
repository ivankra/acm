// DP, Catalan numbers
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

int main()
{
    vector<long long> a(60, 0);
    a[0] = 1;
    a[2] = 1;
    for (int n = 2; n <= 50; n += 2) {
      a[n] = 0;
      for (int k = 1; k < n; k += 2) {
        a[n] += a[k-1] * a[n-1-k];
      }
    }

    int N;
    int first = 1;
    while (scanf("%d", &N) == 1) {
    	if (!first) printf("\n");
    	printf("%lld\n", a[2*N]);
    	first = 0;
    }
}
