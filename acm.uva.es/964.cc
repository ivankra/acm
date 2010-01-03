#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <vector>
#include <string>
#include <map>
using namespace std;

struct Line {
	int cmd;
	int argNum;
	int argVar;
};

struct Var {
	int value;
	int written;
	Var() : value(0), written(0) {}
};

vector<Line> code;
vector<int> data, out, stk;
map<string, int> symMap;
vector<Var> sym;

bool is_var(const char *arg) {
	if (arg[0] == 0 || !isalpha(arg[0])) return false;
	for (; *arg; arg++)
		if (!isalnum(*arg)) return false;
	return true;
}

bool push(int x) { stk.push_back(x); return true; }
int pop() { assert(stk.size() > 0); int x = stk.back(); stk.pop_back(); return x; }

bool push(const Line &l) {
	if (l.argVar >= 0) {
		if (sym[l.argVar].written != 0) return push(sym[l.argVar].value);
	} else {
		return push(l.argNum);
	}
	return false;
}

const char *commands[] = {
	"PUSH", "POP", "DUP", "ADD", "MUL", "SUB", "DIV",
	"READ", "WRITE", "JUMP", "JUMPPOS", "JUMPZERO", NULL
};
	
bool run() {
	const bool jump_to_undef = false;
	int cp = 0, dp = 0;

	stk.clear(); out.clear();
	while (0 <= cp && cp < (int)code.size()) {
		const Line &l = code[cp++];

		if (l.cmd == 0) {		// PUSH
			if (!push(l)) return false;
		} else if (l.cmd == 1) {	// POP
			if (l.argVar < 0 || stk.size() == 0) return false;
			sym[l.argVar].value = pop();
			sym[l.argVar].written = 1;
		} else if (l.cmd == 2) {	// DUP
			if (stk.size() == 0) return false;
			push(stk.back());
		} else if (l.cmd == 3) {	// ADD
			if (stk.size() < 2) return false;
			push(pop() + pop());
		} else if (l.cmd == 4) {	// MUL
			if (stk.size() < 2) return false;
			push(pop() * pop());
		} else if (l.cmd == 5) {	// SUB
			if (stk.size() < 2) return false;
			int x = pop();
			int y = pop();
			push(x - y);
		} else if (l.cmd == 6) {	// DIV
			if (stk.size() < 2) return false;
			int x = pop();
			int y = pop();
			if (y == 0) return false;
			push(x / y);
		} else if (l.cmd == 7) {	// READ
			if (dp >= (int)data.size()) return false;
			push(data[dp++]);
		} else if (l.cmd == 8) {	// WRITE
			if (stk.size() == 0) return false;
			out.push_back(pop());
		} else if (l.cmd == 9) {	// JUMP
			if (!push(l)) return jump_to_undef;
			cp = pop()-1;
		} else if (l.cmd == 10) {	// JUMPPOS
			if (stk.size() == 0) return false;
			if (pop() > 0) {
				if (!push(l)) return jump_to_undef;
				cp = pop()-1;
			}
		} else {			// JUMPZERO
			if (stk.size() == 0) return false;
			if (pop() == 0) {
				if (!push(l)) return jump_to_undef;
				cp = pop()-1;
			}
		}
	}

	return true;	
}

int main()
{
	static char s[100000];

	for (;;) {
		code.clear(); sym.clear(); symMap.clear();
		for (;;) {
			if (gets(s) == NULL) return 0;
			if (s[0] == '#') break;
			for (int m = strlen(s); m > 0 && isspace(s[m-1]);) s[--m] = 0;

			assert(isalpha(s[0]));

			char *p = s;
			while (*p && !isalpha(*p)) p++;
			assert(isalpha(*p));

			char op[20];
			{int i; for (i = 0; i < 15 && *p && isalpha(*p);) op[i++] = *p++; op[i] = 0;}
			while (*p && isspace(*p)) p++;

			Line l;
			for (int i = 0; ; i++) {
				assert(commands[i] != NULL);
				if (strcmp(commands[i], op) == 0) {
					l.cmd = i;
					break;
				}
			}

			for (int i = 0; p[i]; i++) assert(isalnum(p[i]) || p[i] == '-');

			l.argNum = 0;
			l.argVar = -1;

			if (isalpha(*p)) {
				if (symMap.count(p) == 0) {
					symMap[p] = l.argVar = sym.size();
					sym.push_back(Var());
				} else {
					l.argVar = symMap[p];
				}
			} else {
				l.argNum = atoi(p);
			}

			code.push_back(l);
		}

		data.clear();
		for (;;) {
			if (gets(s) == NULL) return 0;
			if (s[0] == '#') break;
			data.push_back(atoi(s));
		}

		if (!run()) {
			printf("ABORTED\n");
		} else {
			for (int i = 0; i < (int)out.size(); i++)
				printf("%d\n", out[i]);
		}
		printf("#\n");
	}
}
