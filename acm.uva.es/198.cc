#include <cstdio>
#include <cstring>
#include <cctype>
#include <cassert>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

char toksrc[1024], toks[1024], *tokp;
int tok;
long long tokn;

struct Symbol {
	string s;
	int def;
	long long val;
	vector<int> dep;
};

map<string, int> symmap;
vector<Symbol> symtab;

int symbol(const string &nm, bool creat) {
	if (symmap.count(nm) > 0) return symmap[nm];
	if (!creat) return -1;

	int id = symtab.size();
	symmap[nm] = id;
	Symbol sy;
	sy.s = "";
	sy.def = 0;
	sy.dep.clear();
	symtab.push_back(sy);
	return id;
}

int lookup(const string &nm) { return symbol(nm, false); }

int next() {
	while (*tokp && isspace(*tokp)) tokp++;
	if (*tokp == '\0') return tok = EOF;

	if (*tokp == ':') {
		assert(tokp[1] == '='); tokp += 2;
		return tok = '=';
	}

	if (strchr("+-*()", *tokp) != NULL) return tok = *tokp++;

	if (isdigit(*tokp)) {
		for (tokn = 0; *tokp && isdigit(*tokp); tokp++)
			tokn = tokn * 10LL + *tokp - '0';
		return tok = 'n';
	}

	if (isalpha(*tokp)) {
		int i;
		for (i = 0; *tokp && isalnum(*tokp);)
			toks[i++] = *tokp++;
		toks[i] = 0;
		return tok = 'a';
	}

	assert(0==1);
	return EOF;
}

long long g_expr();

long long g_fact() {
	while (tok == '+') next();

	if (tok == '-') {
		next();
		return -g_fact();
	}

	if (tok == '(') {
		next();
		long long x = g_expr();
		assert(tok == ')');
		next();
		return x;
	}

	if (tok == 'a') {
		int v = lookup(string(toks));
		next();
		assert(v >= 0 && symtab[v].def == 1);
		return symtab[v].val;
	}

	assert(tok == 'n');
	long long x = tokn;
	next();
	return x;
}

long long g_term() {
	long long x = g_fact();
	while (tok == '*') {
		next();
		x *= g_fact();
	}
	return x;
}

long long g_expr() {
	long long x = g_term();
	for (;;) {
		if (tok == '+') {
			next();
			x += g_term();
		} else if (tok == '-') {
			next();
			x -= g_term();
		} else {
			break;
		}
	}
	return x;
}

int eval(int v) {
	if (v < 0 || symtab[v].def < 0) return 1;
	if (symtab[v].def == 1) return 0;

	symtab[v].def = -1;

	strcpy(tokp = toksrc, symtab[v].s.c_str());
	vector<int> dep;
	while (next() != EOF) {
		if (tok == 'a') {
			int d = lookup(string(toks));
			if (d < 0) return 1;
			dep.push_back(d);
		}
	}

	for (int i = 0; i < (int)dep.size(); i++)
		if (eval(dep[i])) return 1;
	dep.clear();

	strcpy(tokp = toksrc, symtab[v].s.c_str());
	next();
	symtab[v].val = g_expr();
	symtab[v].def = 1;
	return 0;
}

int print(const string &nm) {
	int s = lookup(nm);
	if (s < 0) return 1;

	for (int i = 0; i < (int)symtab.size(); i++)
		symtab[i].def = 0;

	if (eval(s) || symtab[s].def != 1) return 1;
	printf("%lld\n", symtab[s].val);
	return 0;
}

int main()
{
	symtab.clear();
	symmap.clear();
	while (gets(toksrc)) {
		tokp = toksrc;
		if (next() != 'a') continue;

		assert(tok == 'a');
		if (strcmp(toks, "PRINT") == 0) {
			next();
			assert(tok == 'a');
			if (print(string(toks))) printf("UNDEF\n");
		} else if (strcmp(toks, "RESET") == 0) {
			symtab.clear();
			symmap.clear();
		} else {
			int v = symbol(string(toks), true);
			next();
			assert(tok == '=');
			symtab[v].s = string(tokp);
		}
	}
}
