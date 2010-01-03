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

int main()
{
	for (;;) {
		double mp[256];
		bool got[256];
		memset(got, 0, sizeof(got));

		for (int i = 0; i < 2; i++) {
			char ch;
			scanf(" %c", &ch);
			if (ch == 'E') return 0;
			scanf("%lf", &mp[ch]);
			got[ch] = true;
		}
    
		if (!got['H']) {
			double e = 6.11 * exp(5417.7530 * ((1/273.16) - (1/(mp['D']+273.16))));
			mp['H'] = mp['T'] + (0.5555)*(e - 10.0);
		} else if (!got['T']) {
			double e = 6.11 * exp(5417.7530 * ((1/273.16) - (1/(mp['D']+273.16))));
			mp['T'] = mp['H'] - (0.5555)*(e - 10.0);
		} else {
			double e = 10 + (mp['H'] - mp['T'])/0.5555;
			mp['D'] = -1/(log(e/6.11) / 5417.7530 - 1/273.16) - 273.16;
		}

		printf("T %.1f D %.1f H %.1f\n", mp['T'], mp['D'], mp['H']);
	}
}
