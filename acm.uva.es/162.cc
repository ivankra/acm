#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> VI;

VI getdeck() {
	VI r;
	int c;
	while (r.size() < 52) {
		while ((c = getchar()) != EOF && c != '#' && !isalpha(c));
		if (c == '#') return VI();
		while ((c = getchar()) != EOF && !isalnum(c));
		r.push_back(toupper(c));
	}
	return r;
}

int rank(int c) {
	if (c == 'J') return 1;
	if (c == 'Q') return 2;
	if (c == 'K') return 3;
	if (c == 'A') return 4;
	return 0;
}

void play(VI deck) {
	VI h[2], z;
	int p = 0;

	for (int i = 0; i < 52; i++)
		h[i % 2].push_back(deck[i]);

	while (h[p].size() > 0) {
		z.clear();
		int c, last = -1;

/*printf("non dealer%s", p==0?"*":" ");
for (int i = h[0].size()-1; i >= 0; i--) printf(" %c",h[0][i]);printf("\n");
printf("dealer%s    ", p==1?"*":" ");
for (int i = h[1].size()-1; i >= 0; i--) printf(" %c",h[1][i]);printf("\n");
*/
		for (;;) {
			if (h[p].size() == 0) goto done;
			c = h[p].back(); h[p].pop_back();
			z.push_back(c);
//printf("%c throws %c\n", "nd"[p], c);
			p ^= 1;
			if (rank(c) != 0) { last=1-p; break; }
		}

		for (;;) {
			int i, r = rank(c);
			for (i = 0; i < r; i++) {
				if (h[p].size() == 0) goto done;
				c = h[p].back(); h[p].pop_back();
//printf("%c throws %c\n", "nd"[p], c);
				z.push_back(c);
				if (rank(c) != 0) { last = p; break; }
			}
			if (i >= r) break;
			p ^= 1;
		}

//printf("%c grabs cards\n", "nd"[last]);
		VI x;
		while (z.size() > 0) {
			x.push_back(z.back());
			z.pop_back();
		}

		for (int i = 0; i < (int)h[last].size(); i++)
			x.push_back(h[last][i]);
		h[last] = x;

		p = last;
	}

done:	p ^= 1;
	printf("%d%3d\n", 2-p, h[p].size());
}

int main()
{
	for (;;) {
		VI deck = getdeck();
		if (deck.size() != 52) break; else play(deck);
	}
}
