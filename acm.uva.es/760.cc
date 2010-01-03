#include <algorithm>
#include <vector>
#include <sstream>
#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cctype>
using namespace std;

int main()
{
	char s[512], t[512];
	static int f[512][512];

	for (int cs = 1; gets(s) != NULL && gets(t) != NULL; cs++) {
		if (cs > 1) printf("\n");

		int N = strlen(s);
		int M = strlen(t);

		for (int i = 0; i <= N || i <= M; i++)
			f[i][M] = f[N][i] = 0;

		int L = 0;
		for (int i = N-1; i >= 0; i--) {
			for (int j = M-1; j >= 0; j--) {
				f[i][j] = (s[i] == t[j] ? f[i+1][j+1]+1 : 0);
				L >?= f[i][j];
			}
		}

		vector<string> res;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (f[i][j] == L) {
					res.push_back(string(s+i, s+i+L));
					break;
				}
			}
		}

		sort(res.begin(), res.end());
		res.erase(unique(res.begin(), res.end()), res.end());

		if (L == 0) {
			printf("No common sequence.\n");
		} else {
			for (int i = 0; i < res.size(); i++)
				printf("%s\n", res[i].c_str());
		}

		gets(s);
	}
}
