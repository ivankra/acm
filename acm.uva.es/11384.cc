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
#define foreach(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

int main()
{
	int N;
	while (scanf("%d", &N) == 1) {
		int K = 0;
		while (N > 0) {
			K++;
			N = N - (N+1)/2;
		}
		printf("%d\n", K);
	}
}
