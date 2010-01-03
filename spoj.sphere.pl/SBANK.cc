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

struct Record {
	int a[6];
	bool operator <(const Record &rec) const {
		for (int i = 0; i < 6; i++)
			if (a[i] != rec.a[i]) return a[i] < rec.a[i];
		return false;
	}
	bool operator ==(const Record &rec) const {
		return memcmp(a, rec.a, 6 * sizeof(int)) == 0;
	}
};

int main()
{
	int t, n;
	scanf("%d", &t);
	for (int cs = 1; cs <= t && scanf("%d ", &n) == 1; cs++) {
		vector<Record> v(n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < 6; j++)
				scanf("%d", &v[i].a[j]);

		sort(v.begin(), v.end());

		int i, j;
		for (i = 0; i < n;) {
			for (j = i+1; j < n && v[i] == v[j]; j++);
			printf("%.2d %.8d %.4d %.4d %.4d %.4d %d\n",
				v[i].a[0], v[i].a[1], v[i].a[2], v[i].a[3], v[i].a[4], v[i].a[5],
				j-i);
			i = j;
		}
		printf("\n");
	}
}
