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

char src[65536];
int f[65536][3], N;

int main() {
	while (scanf(" %s", src+1) == 1 && strcmp(src+1, "0") != 0) {
		src[0] = '0';
		N = strlen(src);
		f[N][1] = 0;
		f[N][0] = f[N][2] = 1<<30;

		for (int i = N-1; i >= 0; i--) {
			for (int c = -1; c <= 1; c++) {
				f[i][c+1] = 1<<30;
				for (int dig = -1; dig <= 1; dig++) {
					int t = 2 * c + dig - (src[i]-'0');
					if (t < -1 || t > 1) continue;
					f[i][c+1] <?= (dig == 0 ? 0 : 1) + f[i+1][t+1];
				}
			}
		}

		int i, c;
		if (f[1][1] == f[0][1]) { i = 1; c = 0; } else { i = 0; c = 0; }

		string res = "";
		for (; i < N; i++) {
			for (int dig_i = 0; dig_i < 3; dig_i++) {
				int dig = "201"[dig_i] - '1';

				int t = 2 * c + dig - (src[i]-'0');
				if (t < -1 || t > 1) continue;

				if (f[i][c+1] == (dig == 0 ? 0 : 1) + f[i+1][t+1]) {
					res += "+-0"[dig_i];
					c = t;
					break;
				}
			}
		}

		for (i = 0; i < (int)res.size()-1 && res[i] == '0'; i++);
		for (; i < (int)res.size(); i++) putchar(res[i]);
		printf("\n");
	}
}
