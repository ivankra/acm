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

/*
0
1
02
1003
02110004
1003020211100005
02110004100310030202021111000006
1002020211100005021100040211000410031003100302020202111110000007

  1 x k
k-1 x 0
k-2 x 1
k-3 x 02
k-4 x 1003
k-5 x 02110004
...

*/

int hendrie(unsigned long long N)
{
	unsigned long long n = N;
	int k = 0;
	while ((1ULL << k) < n) k++;
	if ((1ULL << k) == n) return k;

	n = (1ULL << k) - n;
	n--;

	if (n < k-1) { return 0; } else { n -= k-1; }
	if (n < k-2) { return 1; } else { n -= k-2; }

	for (int m = 2; ; m++) {
		unsigned long long c = (1ULL << (m-1));
		for (int i = 0; i < k-m-1; i++) {
			if (n < c) {
				return hendrie(2*c-n);
			} else {
				n -= c;
			}
		}
	}
}

int main()
{
	unsigned long long n;
	while (cin >> n) {
		if (n == 0) break;
		cout << hendrie(n) << '\n';		
	}
	return 0;
}
