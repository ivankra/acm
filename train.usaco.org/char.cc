/*
ID: infnty1
TASK: char
LANG: C++
*/
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

char font[600][32], text[1300][32];
int NF, N, sim[600][1300];

struct { int letter, lines, score; } f[1300];

void check(int offs, int c, int *fnt, int m) {
	if (offs+m > N) return;

	int s = f[offs+m].score;
	for (int i = 0; i < m; i++)
		s += sim[fnt[i]][offs+i];

	if (s < f[offs].score) {
		f[offs].score = s;
		f[offs].letter = c;
		f[offs].lines = m;
	}
}

int main()
{
	freopen("font.in", "r", stdin);

	scanf("%d", &NF);
	for (int i = 0; i < NF; i++)
		for (int j = 0; j < 20; j++)
			scanf(" %c", &font[i][j]);

	freopen("char.in", "r", stdin);
	freopen("char.out", "w", stdout);

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < 20; j++)
			scanf(" %c", &text[i][j]);

	for (int i = 0; i < NF; i++) {
		for (int j = 0; j < N; j++) {
			sim[i][j] = 0;
			for (int k = 0; k < 20; k++)
				if (font[i][k] != text[j][k]) sim[i][j]++;
		}
	}

	f[N].score = 0;
	for (int i = N-1; i >= 0; i--) {
		f[i].score = 1<<30;
		f[i].lines = N;

		for (int c = 0; c*20 < NF; c++) {
			int p[32];
			for (int j = 0; j < 20; j++) p[j] = c*20+j;
			check(i, c, p, 20);

			for (int x = 0; x < 20; x++) {
				for (int k = 0, j = 0; k < 20; k++)
					if (k != x) p[j++] = c*20+k;
				check(i, c, p, 19);

				for (int k = 0, j = 0; k < 20; k++) {
					p[j++] = c*20+k;
					if (k == x) p[j++] = c*20+k;
				}
				check(i, c, p, 21);
			}
		}
	}

	for (int i = 0; i < N; i += f[i].lines) {
		int c = f[i].letter;
		putchar(c==0 ? ' ' : ('a'+c-1));
	}
	putchar('\n');
}
