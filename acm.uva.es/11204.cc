// dynamic programming
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
typedef vector<int> VI;
typedef vector<VI> VVI;

int main() {
	int T, N, M;
	cin >> T;

	for (int cs = 1; cs <= T; cs++) {
		cin >> N >> M;

		VVI pref;
		for (int i = 0; i < M; i++) {
			VI v(N, -1);
			for (int j = 0; j < N; j++) {
				int x;
				cin >> x;
				assert(1 <= x && x <= N && v[x-1] < 0);
				v[x-1] = j;
			}
			pref.push_back(v);
		}

		sort(pref.begin(), pref.end());

		long long ways = 1;
		for (int i = 0; i < M;) {
			int k = 0;
			while (i+k < M && pref[i][0] == pref[i+k][0]) k++;
			ways *= k;
			i += k;
		}

		cout << ways << endl;

	}
}
