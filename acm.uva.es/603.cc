#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
using namespace std;
#define REP(i,n) for(int _REP_N=(n),i=0;i<_REP_N;i++)

int main() {
	int ini[50], cur[50], fin[50], n, T;
	char buf[256];
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		if (cs > 1) printf("\n");

		for (n = 0; gets(buf);) {
			if (sscanf(buf, "%d", &ini[n]) != 1) continue;
			if (ini[n] >= 99) break;
			ini[n]--;
			cur[n] = ini[n];
			fin[n] = -1;
			n++;
		}

		int m;
		while (gets(buf) && sscanf(buf, "%d", &m) == 1) {
			m--;

			int i, a = -1;
			for (i = 0; i < n; i++)
				if (fin[i]<0 && (a<0 || (m-cur[a]+200)%20 > (m-cur[i]+200)%20)) a = i;
			if (a < 0) continue;

			int t = (m-cur[a]+200)%20;
			for (int i = 0; i < n; i++)
				if (fin[i] < 0) cur[i] = (cur[i] + t) % 20;
			fin[a] = m;
		}

		for (int i = 0; i < n; i++) {
			if (fin[i] < 0)
				printf("Original position %d did not park\n", ini[i]+1);
			else
				printf("Original position %d parked in %d\n", ini[i]+1, fin[i]+1);
		}
	}
}

