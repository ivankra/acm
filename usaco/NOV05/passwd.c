/*
ID: infnty1
TASK: passwd
LANG: C
*/
/* Algorithm: backtracking with some pruning */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int alpha[32], allowed[256], isvowel[256], L, C, vafter[32], cafter[32];
int pwd[32];

void go(int i, int v, int c)
{
	if (i >= L) {
		if (v <= 0 && c <= 0) {
			for (i = 0; i < L; i++) putchar(alpha[pwd[i]]);
			putchar('\n');
		}
		return;
	}

	pwd[i] = (i == 0) ? 0 : (pwd[i-1] + 1);
	if (vafter[pwd[i]] < v || cafter[pwd[i]] < c) return;

	for (; pwd[i] < C; pwd[i]++)
		go(i+1, v - (vafter[pwd[i]] - vafter[pwd[i]+1]),
			c - (cafter[pwd[i]] - cafter[pwd[i]+1]));
}

int main()
{
	int i, j;

	freopen("passwd.in", "r", stdin);
	freopen("passwd.out", "w", stdout);

	scanf("%d %d", &L, &C);

	memset(allowed, 0, sizeof(allowed));
	for (i = 0; i < C; i++) {
		while ((j = getchar()) != EOF && !isalpha(j));
		allowed[tolower(j)] = 1;
	}

	for (C = 0, i = 'a'; i <= 'z'; i++)
		if (allowed[i]) alpha[C++] = i;

	memset(isvowel, 0, sizeof(isvowel));
	for (i = 0; i < 5; i++)
		isvowel["aeiou"[i]] = 1;

	vafter[C] = cafter[C] = 0;
	for (i = C; i >= 0; i--) {
		vafter[i] = vafter[i+1];
		cafter[i] = cafter[i+1];
		if (isvowel[alpha[i]])
			vafter[i]++;
		else
			cafter[i]++;
	}

	go(0, 1, 2);
	fflush(stdout);

	return 0;
}
