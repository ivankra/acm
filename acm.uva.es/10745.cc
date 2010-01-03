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

struct Word {
	char s[16], orig[16];
	bool dominee;
	int len;
	int next;

	bool operator <(const Word &other) const {
		return len > other.len;
	}
};

Word word[15010];
int N;

enum { HASHMASK = 262143U };
short htab[HASHMASK+1];

unsigned hash(const char *s) {
	unsigned res = 0;
	while (*s) { res = res * 26U + (unsigned)(*s++ - 'a'); }
	return res;
}

int main()
{
	char buf[100];
	int i, j, k;

	N = 0;
	for (i = 1; scanf(" %s", buf) == 1; i++) {
		N++;
		word[i].len = strlen(buf);
		strcpy(word[i].orig, buf);
		sort(buf, buf+strlen(buf));
		strcpy(word[i].s, buf);
	}

	sort(word+1, word+N+1);

	memset(htab, 0, sizeof(htab));
	for (i = 1; i <= N; i++) {
		word[i].dominee = false;
		unsigned h = hash(word[i].s) & HASHMASK;
		word[i].next = htab[h];
		htab[h] = i;
	}

	for (i = 1; i <= N; i++) {
		if (word[i].dominee) continue;
		for (int mask = (1 << word[i].len) - 2; mask > 0; --mask) {
			char *s = word[i].s;
			k = 0;
			for (j = mask; *s; j >>= 1, s++)
				if (j & 1) buf[k++] = *s;
			buf[k] = 0;

			unsigned h = hash(buf) & HASHMASK;
			for (j = htab[h]; j != 0; j = word[j].next) {
				if (strcmp(word[j].s, buf) == 0) {
					word[j].dominee = true;
				}
			}
		}
	}

	vector<string> v;
	for (i = 1; i <= N; i++)
		if (!word[i].dominee) v.push_back(word[i].orig);
	sort(v.begin(), v.end());
	for (i = 0; i < v.size(); i++)
		printf("%s\n", v[i].c_str());
}
