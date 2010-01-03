// algorithm: separately compute mean for even and odd letters with backtracking
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

int P[26]={
	1253,	142,	468,	586,	1368,	69,	101,	70,	625,	44,	0,	497,	315,
	671,	868,	251,	88,	687,	798,	463,	393,	90,	2,	22,	90,	52
};

long long avg_num[2][32][8], avg_den[2][32][8];
int cnt[32], first;

void go(int pos, int sum, int flag) {
	avg_num[flag][first][pos] += sum;
	avg_den[flag][first][pos] += 100;
	if (pos >= 4) return;

	const char *s;
	if (flag == 0) {
		s = "bcdfghjklmnpqrstvwxyz";
	} else {
		s = "aeiou";
	}

	while (*s) {
		int c = *s++ - 'a';
		if (pos == 0)
			first = (flag == 0 ? c : 0);
		if (++cnt[c] <= 2) {
			pos++;
			sum += (2*pos-1+flag)*P[c];
			go(pos, sum, flag);
			sum -= (2*pos-1+flag)*P[c];
			pos--;
		}
		--cnt[c];
	}
}

int main() {
	int T, n;
	char s[256];

	scanf("%d", &T);

	memset(avg_num, 0, sizeof(avg_num));
	memset(avg_den, 0, sizeof(avg_den));
	memset(cnt, 0, sizeof(cnt));
	first = 0;
	go(0, 0, 0);
	go(0, 0, 1);

	for (int cs = 1; cs <= T; cs++) {
		scanf(" %s", s);
		n = strlen(s);

		long long sbc = 0;
		for (int i = 0; i < n; i++)
			sbc += (i+1) * P[toupper(s[i])-'A'];

		first = toupper(s[0]) - 'A';

		int n1 = 0;
		int n2 = 0;
		for (int i = 0; i < n; i++)
			if (i % 2 == 0) n1++; else n2++;

		long long num1 = avg_num[0][first][n1], num2 = avg_num[1][0][n2];
		long long den1 = avg_den[0][first][n1], den2 = avg_den[1][0][n2];
		long long num = num1 * den2 + num2 * den1;
		long long den = den1 * den2;		

		//printf("sbc=%lld/%lld vg=%lld/%lld ", sbc, 100LL, num, den);
		if (sbc * den >= 100 * num)
			printf("above or equal\n");
		else
			printf("below\n");
	}
}
