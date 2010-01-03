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
#include <map>
using namespace std;

int main()
{
	map<pair<int, int>, int> mp;
	pair<int, int> p(0, 0);
	for (int n = 0; n < 25000;) {
		mp[p] = n++; p.first++; p.second++;
		mp[p] = n++; p.first++; p.second--;
		mp[p] = n++; p.first++; p.second++;
		mp[p] = n++; p.first--; p.second++;
	}

	int N;
	scanf("%d", &N);

	for (int cs = 1; cs <= N && scanf("%d %d", &p.first, &p.second) == 2; cs++) {
		if (mp.count(p) == 0)
			printf("No Number\n");
		else
			printf("%d\n", mp[p]);
	}
}
