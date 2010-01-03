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

struct stmt {
	char speaker;
	char type;	// 'D' day, 'N' night, 'I' is/is not
	char who;
	bool not_flag;
	char what;
};

void read(stmt &s) {
	char w[100];
	scanf(" %c : %s", &s.speaker, w);
	if (strcmp(w, "It") == 0) {
		scanf(" is %s .", w);
		s.type = toupper(w[0]);
	} else {
		s.type = 'I';
		s.who = (w[0] == 'I' ? s.speaker : w[0]);
		scanf(" %*s %s", w);
		if (strcmp(w, "not") == 0) {
			s.not_flag = true;
			scanf(" %s", w);
		} else {
			s.not_flag = false;
		}
		s.what = toupper(w[0]);
		scanf(" .");
	}
}

int var[6];

bool lies(char ch) {
	return var[ch-'A'] == 1 || (var[ch-'A'] == 2 && var[5] == 1);
}

bool verify(stmt &s) {
	bool res;
	if (s.type == 'D') {
		res = (var[5] == 0);
	} else if (s.type == 'N') {
		res = (var[5] == 1);
	} else {
		if (s.what == 'D')
			res = (var[s.who-'A'] == 0);
		else if (s.what == 'E')
			res = (var[s.who-'A'] == 1);
		else if (s.what == 'H')
			res = (var[s.who-'A'] == 2);
		else
			res = lies(s.who);

		if (s.not_flag)
			res = !res;
	}

	if (lies(s.speaker))
		res = !res;

	return res;
}

int main() {
	int N;
	stmt s[100];

	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		for (int i = 0; i < N; i++)
			read(s[i]);

		int mask[6];
		memset(mask, 0, sizeof(mask));

		bool impos = true;

		for (var[0] = 0; var[0] <= 2; var[0]++)
		for (var[1] = 0; var[1] <= 2; var[1]++)
		for (var[2] = 0; var[2] <= 2; var[2]++)
		for (var[3] = 0; var[3] <= 2; var[3]++)
		for (var[4] = 0; var[4] <= 2; var[4]++)
		for (var[5] = 0; var[5] <= 1; var[5]++) {
			for (int i = 0; i < N; i++)
				if (!verify(s[i])) goto skip;

			for (int i = 0; i < 6; i++)
				mask[i] |= 1 << var[i];
			impos = false;
skip:;
		}

		printf("Conversation #%d\n", cs);

		if (impos) {
			printf("This is impossible.\n\n");
			continue;
		}

		bool none = true;
		for (int i = 0; i < 6; i++) {
			int val = -1, val_c = 0;
			for (int j = 0; j < 3; j++)
				if (mask[i] & (1 << j)) { val = j; val_c++; }
			if (val_c != 1) continue;

			none = false;

			if (i < 5) {
				char *a[] = { "divine", "evil", "human" };
				printf("%c is %s.\n", i+'A', a[val]);
			} else {
				printf("It is %s.\n", val == 0 ? "day" : "night");
			}
		}
		if (none)
			printf("No facts are deducible.\n");
		printf("\n");
	}
}
