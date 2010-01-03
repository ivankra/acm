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

	vector<string> a(N+1, string(M, '0'));

	for (int i = 0; i < M; i++) {
		int k, r;
		cin >> k;
		for (int j = 0; j < k; j++) {
			cin >> r; r--;
			a[r][i] = '1';
		}
	}

	sort(a.begin(), a.end());
	a.erase(unique(a.begin(), a.end()), a.end());

	cout << (a.size()-1) << endl;
}
