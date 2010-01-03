#include <algorithm>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;


int main()
{
	char buf[1024];
	int T;

	gets(buf);
	sscanf(buf, "%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		gets(buf);
		int N = strlen(buf);

		static int f[1024][1024];

		for (int i = 0; i < N; i++) f[0][i] = 0;
		for (int i = 0; i < N; i++) f[1][i] = 1;

		for (int m = 2; m <= N; m++) {
			for (int s = 0; s+m <= N; s++) {
				if (buf[s] == buf[s+m-1])
					f[m][s] = f[m-2][s+1] + 2;
				else
					f[m][s] = max(f[m-1][s], f[m-1][s+1]);
			}
		}

		printf("%d\n", f[N][0]);
	}
}
