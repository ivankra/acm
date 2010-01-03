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

long long d[50][26][26], spec[26];

int main()
{
	int N;
	while (scanf("%d", &N) == 1) {
		memset(d, 0, sizeof(d));
		memset(spec, 0, sizeof(spec));
		for (int i = 0; i < 26; i++) d[0][i][i] = 1;
		for (int i = 0; i < N; i++) {
			char x, y1, y2, flag;
			scanf(" %c %c %c %c", &x, &y1, &y2, &flag);
			x = toupper(x); y1 = toupper(y1); y2 = toupper(y2);
			++d[1][x-'A'][y1-'A'];
			++d[1][x-'A'][y2-'A'];
			if (flag != '-') ++spec[x-'A'];
		}

		scanf("%d", &N);
		for (int k = 2; k <= N; k++) {
			for (int x = 0; x < 26; x++) {
				for (int y = 0; y < 26; y++) {
					for (int z = 0; z < 26; z++) {
						d[k][x][y] += d[k-1][x][z] * d[1][z][y];
					}
				}
			}
		}

		long long res = 0;
		for (int i = 0; i < 26; i++)
			res += spec[i] * d[N][0][i];
		printf("%lld\n", res);
	}
}
