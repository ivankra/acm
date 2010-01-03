#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int type[32], len[32], list[32][32], flag[32][32], eqtab[32][32], id, tok;

int eq(int s, int t)
{
	int i;

	if (eqtab[s][t] >= 0) return eqtab[s][t];
	if (eqtab[t][s] >= 0) return (eqtab[s][t] = eqtab[t][s]);

	if (s == t) return (eqtab[s][t] = 1);
	if (type[s] == type[t] && type[s] != 's') return (eqtab[s][t] = 1);

	if (flag[s][t] == id) return 1;

	if (isupper(type[s])) {
		flag[s][t] = id;
		return (eqtab[s][t] = eq(type[s] - 'A', t));
	}

	if (isupper(type[t])) {
		flag[s][t] = id;
		return (eqtab[s][t] = eq(s, type[t] - 'A'));
	}

	if (type[s] != 's' || type[t] != 's' || len[s] != len[t])
		return (eqtab[s][t] = 0);

	flag[s][t] = id;
	for (i = 0; i < len[s]; i++)
		if (!eq(list[s][i] - 'A', list[t][i] - 'A'))
			return (eqtab[s][t] = 0);

	return (eqtab[s][t] = 1);
}

int next()
{
	int c;

	while ((c = getchar()) != EOF) {
		if (strchr("()=-", c) != NULL || isupper(c))
			return (tok = c);

		if (islower(c)) {
			for (tok = c; (c = getchar()) != EOF && isalpha(c););
			if (c != EOF) ungetc(c, stdin);
			return tok;
		}		
	}

	return (tok = EOF);
}

int main()
{
	int i, j, k, t, g[32];

	id = 42;

	for (next(), t = 0; tok != EOF && tok != '-';) {
		if (t++) printf("\n");

		for (i = 0; i < 32; i++) type[i] = len[i] = 0;

		while (tok == 't') {
			k = next() - 'A';
			assert(0 <= k && k < 26);

			i = next();
			assert(i == '=');

			type[k] = next();
			if (type[k] != 's') {
				next();
				continue;
			}

			i = next();
			assert(i == '(');

			for (next(); tok != ')'; next()) {
				assert('A' <= tok && tok <= 'Z');
				list[k][len[k]++] = tok;
			}
			
			assert(tok == ')');
			next();
		}

		assert(tok == '-');
		next();

		for (i = 0; i < 26; i++) {
			for (j = 0; j < 26; j++)
				eqtab[i][j] = -1;
			eqtab[i][i] = 1;
		}

		for (i = 0; i < 26; i++) {
			if (type[i] == 0) continue;
			for (j = 0; j < 26; j++)
				if (type[j] != 0) {
					id++;
					eq(i, j);
				}
		}

		for (i = 0; i < 26; i++)
			g[i] = 0;

		for (i = j = 0; i < 26; i++) {
			if (type[i] == 0 || g[i] > 0) continue;
			for (g[i] = ++j, k = i + 1; k < 26; k++)
				if (type[k] != 0 && g[k] == 0 && eq(i,k))
					g[k] = j;
		}

		for (k = 1; k <= j; k++) {
			for (i = 0; i < 26 && g[i] != k; i++);
			printf("%c", i+'A');
			for (i++; i < 26; i++)
				if (g[i] == k) printf(" %c", i+'A');
			printf("\n");
		}
	}

	return 0;	
}
