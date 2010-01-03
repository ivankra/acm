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
#include <queue>
using namespace std;


int main()
{
	int T, N;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		vector<string> table(200, "");
		int K = 0;

		scanf("%d", &N);
		for (int op = 0; op < N; op++) {
			char cmd[100], buf[100];
			scanf(" %[a-zA-Z] : %s", cmd, buf);

			string s = string(buf);
			int h = 0;
			for (int i = 0; i < s.size(); i++)
				h = (h + 19 * (i+1) * s[i]) % 101;

			if (cmd[0] == 'a' || cmd[0] == 'A') {
				bool exists = false;
				for (int j = 0; j <= 19; j++) {
					int i = (h + j*j + 23*j) % 101;
					exists |= (table[i] == s);
				}

				if (!exists) {
					for (int j = 0; j <= 19; j++) {
						int i = (h + j*j + 23*j) % 101;
						if (table[i] == "") {
							table[i] = s;
							K++;
							break;
						}
					}
				}
			} else {
				for (int j = 0; j <= 19; j++) {
					int i = (h + j*j + 23*j) % 101;
					if (table[i] == s) {
						table[i] = "";
						K--;
						break;
					}
				}
			}
		}

		printf("%d\n", K);
		for (int i = 0; i < 101; i++)
			if (table[i] != "") printf("%d:%s\n", i, table[i].c_str());
	}
}
