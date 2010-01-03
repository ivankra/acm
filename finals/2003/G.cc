// ICPC Finals 2003 - Problem G - A Linking Loader
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <string>
using namespace std;

struct Symbol {
	string name;
	int offset, defined;
	vector<int> ref;

	Symbol(const string &name_) : name(name_), offset(0), defined(0) {}
};

map<string, Symbol *> symtab;
unsigned char code[65536];
int codeSize;

int moduleOffs;
vector<Symbol *> moduleExt;

void processC(char *line)
{
	// C n byte1 byte2 ...byten'
	unsigned n, x;
	int delta;

	sscanf(line, "C %X %n", &n, &delta);
	line += delta;

	while (n > 0) {
		while (*line && isspace(*line)) line++;
		assert(*line != 0);

		if (line[0] == '$') {
			assert(n >= 2);
			n -= 2;
			line++;
			sscanf(line, " %X %n", &x, &delta);
			line += delta;
			assert(x < moduleExt.size());
			moduleExt[x]->ref.push_back(codeSize);
			code[codeSize++] = 0;
			code[codeSize++] = 0;
		} else {
			sscanf(line, " %X %n", &x, &delta);
			line += delta;
			code[codeSize++] = x;
			n--;
		}
	}
}

void processD(char *line)
{
	// D symbol offset
	char name[50]; unsigned offs;
	sscanf(line, "D %s %X", name, &offs);

	if (symtab.count(name) != 0) {
		Symbol *s = symtab[name];
		if (s->defined == 0) {
			s->offset = moduleOffs + offs;
		}
		s->defined++;
	} else {
		Symbol *s = new Symbol(name);
		s->defined = 1;
		s->offset = moduleOffs + offs;
		symtab[name] = s;
	}
}

void processE(char *line)
{
	// E symbol
	char name[50];
	sscanf(line, "E %s", name);

	if (symtab.count(name) == 0) {
		Symbol *s = new Symbol(name);
		symtab[name] = s;
	}

	moduleExt.push_back(symtab[name]);
}

void next(char *line) {
	line[0] = 0;
	gets(line);
	assert(strchr("DECZ$", line[0]) != NULL);
}

int main()
{
	char line[1024];
	next(line);

	for (int cs = 1; line[0] != '$'; cs++) {
		for (map<string, Symbol *>::const_iterator it = symtab.begin(); it != symtab.end(); ++it) {
			delete it->second;
		}
		symtab.clear();

		memset(code, 0, 0x100);
		codeSize = 0x100;

		while (true) {
			if (line[0] == '$') {
				next(line);
				break;
			}

			moduleOffs = codeSize;
			moduleExt.clear();

			while (true) {
				if (line[0] == 'D') {
					processD(line);
				} else if (line[0] == 'E') {
					processE(line);
				} else if (line[0] == 'C') {
					processC(line);
				} else if (line[0] == 'Z') {
					next(line);
					break;
				} else {
					abort();
				}
				next(line);
			}
		}

		// resolve symbols
		for (map<string, Symbol *>::const_iterator it = symtab.begin(); it != symtab.end(); ++it) {
			Symbol *s = it->second;
			for (int i = 0; i < (int)s->ref.size(); i++) {
				int j = s->ref[i];
				code[j] = (s->offset >> 8) & 0xFF;
				code[j+1] = s->offset & 0xFF;
			}
		}

		unsigned checksum = 0;
		for (int i = 0; i < codeSize; i++) {
			checksum = ((checksum << 1) | ((checksum >> 15) & 1)) & 0xFFFF;
			checksum = (checksum + code[i]) & 0xFFFF;
		}

		if (cs > 1) printf("\n");
		printf("Case %d: checksum = %.4X\n", cs, checksum);
		printf(" SYMBOL   ADDR\n");
		printf("--------  ----\n");
		for (map<string, Symbol *>::const_iterator it = symtab.begin(); it != symtab.end(); ++it) {
			Symbol *s = it->second;
			printf("%-10s", s->name.c_str());
			if (s->defined == 0) {
				printf("????\n");
			} else {
				printf("%.4X%s\n", s->offset, s->defined > 1 ? " M" : "");
			}
		}
	}
}
