#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;

struct Partial {
	char a[28];
	int used;
	bool operator <(const Partial &c) const { return memcmp(a, c.a, 27) < 0; }
	void print() { a[27] = 0; printf("%s\n", a); }
	void xprint() {
		for (int i = 0; i < 27; i++) putchar(a[i] ? a[i] : '.');
		putchar('\n');
	}
	void fix_used() {
		used = 0;
		for (int i = 0; i < 27; i++)
			if (a[i] != 0) used |= 1 << i;
	}
};

struct Figure {
	Partial *c;
	int n;
} figure[7];

void doit(Partial *cur, int fig) {
	if (fig == 7) { cur->print(); return; }

	Partial *p = figure[fig].c, next;
	for (int i = figure[fig].n; i-- > 0; p++) {
		if ((cur->used & p->used) == 0) {
			for (int j = 0; j < 27; j++)
				next.a[j] = cur->a[j] | p->a[j];
			next.used = cur->used | p->used;
			doit(&next, fig+1);
		}
	}
}

char RX[]={7,8,9,16,17,18,25,26,27,4,5,6,13,14,15,22,23,24,1,2,3,10,11,12,19,20,21};
char RY[]={7,4,1,8,5,2,9,6,3,16,13,10,17,14,11,18,15,12,25,22,19,26,23,20,27,24,21};
char RZ[]={3,12,21,6,15,24,9,18,27,2,11,20,5,14,23,8,17,26,1,10,19,4,13,22,7,16,25};
char RA[64][32];

void rot(char *s, char *tab) {
	char t[32];
	for (int i = 0; i < 27; i++) t[tab[i]-1] = s[i];
	for (int i = 0; i < 27; i++) s[i] = t[i];
}

void make_rots() {
	char c[28];
	for (int i = 0; i < 27; i++) c[i] = i+1;

	int k = 0;
	for (int x = 0; x < 4; x++, rot(c, RX))
	for (int y = 0; y < 4; y++, rot(c, RY))
	for (int z = 0; z < 4; z++, rot(c, RZ)) {
		memcpy(RA[k++], c, 27);
		for (int i = 0; i < k-1; i++)
			if (memcmp(RA[i], RA[k-1], 27) == 0) { k--; break; }
	}
	assert(k == 24);
}

bool trans(char s[], int dx, int dy, int dz) {
	char t[28];
	for (int i = 0; i < 27; i++) t[i] = 0;

	for (int x = 0; x < 3; x++)
	for (int y = 0; y < 3; y++)
	for (int z = 0; z < 3; z++) {
		int c = s[9*y+3*z+x];
		if (c != 0) {
			if (x+dx < 0 || x+dx > 2) return false;
			if (y+dy < 0 || y+dy > 2) return false;
			if (z+dz < 0 || z+dz > 2) return false;
			t[9*(y+dy)+3*(z+dz)+(x+dx)] = c;
		}
	}

	for (int i = 0; i < 27; i++) s[i] = t[i];
	return true;
}

int main()
{
	make_rots();

	for (int fig = 'b'; fig <= 'g'; fig++) {
		vector<Partial> res;
		set<Partial> S;

		for (int r = 0; r < 24; r++)
		for (int dx = -3; dx <= 3; dx++)
		for (int dy = -3; dy <= 3; dy++)
		for (int dz = -3; dz <= 3; dz++) {
			Partial c;

			char *pieces = "adcaccaacddgbfgffedggbfebee";
			for (int i = 0; i < 27; i++)
				c.a[i] = (pieces[i] == fig) ? fig : 0;

			rot(c.a, RA[r]);
			if (!trans(c.a, dx, dy, dz)) continue;

			if (S.count(c) == 0) {
				c.fix_used();
				res.push_back(c);
				S.insert(c);
			}
		}

		Figure &F = figure[fig-'a'];
		F.n = res.size();
		F.c = new Partial[F.n];
		for (int i = 0; i < F.n; i++)
			F.c[i] = res[i];
	}

	for (;;) {
		Partial C;
		for (int i = 0; i < 27; i++) {
			int c;
			while ((c = getchar()) != EOF && c != '.' && c != 'a');
			if (c == EOF) return 0;
			C.a[i] = (c == 'a') ? 'a' : 0;
		}

		for (int dx = -3; dx <= 3; dx++)
		for (int dy = -3; dy <= 3; dy++)
		for (int dz = -3; dz <= 3; dz++) {
			Partial D = C;
			if (!trans(D.a, dx, dy, dz)) continue;
			D.fix_used();
			doit(&D, 1);
		}
		printf("\n");
	}
}
