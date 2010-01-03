#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

int main()
{
	int n;
	while (scanf("%d", &n) == 1 && n > 0) {
		vector<int> v(n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &v[i]);
			v[i]--;
		}

		bool ambig = true;
		for (int i = 0; i < n; i++) {
			if (v[v[i]] != i) {
				ambig = false;
				break;
			}
		}

		printf(ambig ? "ambiguous\n" : "not ambiguous\n");
	}
}
