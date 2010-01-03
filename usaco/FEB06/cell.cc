/*
ID: infnty1
TASK: cell
LANG: C++
*/
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <algorithm>
using namespace std;
typedef unsigned long long u64;

int B, L, D;
char dict[1024][16], best[65536];
int best_words, bstart[32], blen[32], but[32];

static inline u64 encode(char *s) {
	u64 r = 0;
	for (; *s; s++)
		r = r * B + but[*s-'A'];
	return r;
}

#define DIV 9999991

int hgot[DIV], hgotid;
int htab[DIV];

struct {
	u64 val;
	int len, count, next;
} hent[65536];
int nent;

void gowork() {
	static char sol[65536];

	char *q = sol;
	for (int i = 0; i < B; i++) {
		for (int j = 0; j < blen[i]; j++) {
			but[bstart[i] + j] = i;
			*q++ = 'A' + bstart[i] + j;
		}
		*q++ = '\n';
	}
        *q = '\0';

//	printf("testing: %s ", sol);

	hgotid++;
	nent = 0;

	for (int i = 0; i < D; i++) {
		u64 w = encode(dict[i]);
		int len = strlen(dict[i]);

		unsigned h = (unsigned)(w % DIV);

		if (hgot[h] != hgotid) {
			hgot[h] = hgotid; htab[h] = 0;
		} else {
			for (int p = htab[h]; p != 0; p = hent[p].next) {
				if (hent[p].val == w && hent[p].len == len) {
					hent[p].count++;
					goto nxt;
				}
			}
		}

		nent++;
		hent[nent].val = w;
		hent[nent].len = len;
		hent[nent].count = 1;
		hent[nent].next = htab[h];
		htab[h] = nent;

nxt:		;
	}

	int nuniq = 0;
	for (int i = 1; i <= nent; i++)
		if (hent[i].count == 1) nuniq++;

	if (nuniq > best_words) {
		best_words = nuniq;
		strcpy(best, sol);
	}

//	printf(" %d\n", nuniq);
}

void gopart(int pos, int left) {
	if (pos > B) return;
	if (pos == B) {
		if (left == 0) gowork();
		return;
	}
	if (left <= 0) return;
	bstart[pos] = (pos == 0 ? 0 : (bstart[pos-1] + blen[pos-1]));
	for (blen[pos] = left; blen[pos] >= 1; blen[pos]--) {
		if (bstart[pos] + blen[pos] > L) continue;
		gopart(pos+1, left - blen[pos]);
	}
}

int main()
{
	scanf("%d %d %d", &B, &L, &D);
//	printf("buttons=%d letters=%d  |dict|=%d\n", B, L, D);

	for (int i = 0; i < D; i++)
		scanf(" %[A-Z]", dict[i]);

	best_words = -1;
	best[0] = 0;
	memset(hgot, 0, sizeof(hgot));
	hgotid = 42;

	gopart(0, L);

	int id = 1;

	printf("#FILE cell %d\n", id);
	printf("%d\n", best_words);
	printf("%s", best);

	return 0;
}
