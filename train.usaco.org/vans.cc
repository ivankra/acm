/*
ID: infnty1
TASK: vans
LANG: C++
*/
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <map>
using namespace std;

typedef vector<int> big;
const int RADIX = 1000000000;

void set(vector<int> &v, int n) {
	v.clear();
	if (n > 0) v.push_back(n);
}

vector<int> operator +(const vector<int> &a, const vector<int> &b) {
	vector<int> res;
	for (int i = a.size()-1, j = b.size()-1, c = 0;; i--, j--, c /= RADIX) {
		if (i < 0 && j < 0 && c == 0) break;
		if (i >= 0) c += a[i];
		if (j >= 0) c += b[j];
		res.push_back(c % RADIX);
	}
	reverse(res.begin(), res.end());
	return res;
}

void print(const vector<int> &v) {
	if (v.size() == 0) {
		printf("0\n");
	} else {
		for (int i = 0; i < (int)v.size(); i++)
			printf(i==0 ? "%d" : "%.9d", v[i]);
		printf("\n");
	}
}

big f[1024][6];

int main() {
	freopen("vans.in", "r", stdin);
	freopen("vans.out", "w", stdout);

	int N;
	scanf("%d", &N);

	for (int i = 0; i < 6; i++)
		set(f[0][i], (i == 0 ? 2 : 0));

	for (int n = 1; n <= N; n++) {
		set(f[n][0], 0);
		f[n][1] = f[n-1][0] + f[n-1][2] + f[n-1][3] + f[n-1][4] + f[n-1][4];
		f[n][2] = f[n-1][0] + f[n-1][2] + f[n-1][4] + f[n-1][4];
		f[n][3] = f[n-1][1];
		f[n][4] = f[n-1][1] + f[n-1][5];
		f[n][5] = f[n-1][1] + f[n-1][5];
	}

	print(f[N-1][1] + f[N-1][5]);
}
