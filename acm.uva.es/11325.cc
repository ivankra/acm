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
#include <set>
using namespace std;

int enemy[26], my[13];

bool rec(int i) {
	if (i == 26) {
		return true;
	}

	for (int r = 0; r < 13; r++) {
		if (my[r] == 0) continue;
		if (enemy[i] > r) continue;

		if (enemy[i] < r) {
			--my[r];
			if (rec(i+1)) {
				return true;
			}
			++my[r];

			break;

		} else {
			if (i == 25) continue;

			--my[r];
			int j = min(i + 4, 25);
			if (rec(j)) {
				return true;
			}
			++my[r];
		}
	}

	return false;
}

int readCard() {
	char rank, suit;
	scanf(" %c %c", &rank, &suit);

	const char *s = "23456789TJQKA";
	return strchr(s, toupper(rank)) - s;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		for (int i = 0; i < 13; i++) my[i] = 4;
		for (int i = 0; i < 26; i++) {
			int x = readCard();
			enemy[i] = x;
			--my[x];
			assert(my[x] >= 0);
		}

		if (rec(0)) {
			printf("yes\n");
		} else {
			printf("no\n");
		}
	}
}
