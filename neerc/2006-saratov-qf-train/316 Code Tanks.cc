#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
using namespace std;

int main()
{
	int N, M;
	cin >> N >> M;

	vector<int> hp(N, 100), sc(N, 0);
	for (int i = 0; i < M; i++) {
		int s, t;
		cin >> s >> t;
		s--; t--;

		if (hp[t] > 0) sc[s] += 3;
		hp[t] -= 8;
	}

	for (int i = 0; i < N; i++) {
		if (hp[i] > 0) sc[i] += hp[i] / 2;
		printf("%d %d\n", hp[i], sc[i]);
	}
}
