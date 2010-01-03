#include <cstdio>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<string> VS;  typedef vector<VS> VVS;

VS tokenize(const string &s) {
	VS ret;
	for (int i = 0, j;;) {
		while (i < (int)s.size() && isspace(s[i])) i++;
		if (i >= (int)s.size()) return ret;
		if (s[i] == '\"') {
			for (j = i++; i < (int)s.size() && s[i] != '\"'; i++);
			if (i < (int)s.size()) i++;
		} else {
			for (j = i; i < (int)s.size() && !isspace(s[i]); i++);
		}
		ret.push_back(s.substr(j, i-j));
	}
}

struct Grammar {
	VS tok;
	int pos;

	Grammar(VS v) : tok(v), pos(0) {}
	bool end() { return pos >= (int)tok.size(); }
	bool is(const string &s) { return !end() && tok[pos] == s; }
	bool match(const string &s) {
		if (is(s)) { pos++; return true; }
                return false;
	}

	int ins() {
		if (is("GO") || is("KEEP")) {
			for (;;) {
				if (!dir()) return 0;
				if (match("AND")) {
					if (match("THEN")) continue;
					return time() && end();
				}
				return end();
			}
		}
		return time() && end();
	}

	int dir() {
		if (match("GO"))
			match("FIRST") || match("SECOND") || match("THIRD");
		else if (!match("KEEP"))
			return 0;
		if (!match("LEFT") && !match("RIGHT")) return 0;
		if (match("AT") && !match("quoted")) return 0;
		return 1;
	}

	int time() {
		if (match("RECORD")) return match("TIME");

		if (match("CHANGE")) {
			if (!match("AVERAGE") || !match("SPEED")) return 0;
		} else if (!match("CAS")) {
			return 0;
		}

		return match("TO") && match("number") && match("KMH");
	}
/*
instruction = navigational | time-keeping | navigational AND time-keeping
navigational = directional | navigational AND THEN directional
directional = how direction | how direction AT sign
how = GO | GO when | KEEP
direction = RIGHT | LEFT
when = FIRST | SECOND | THIRD
time = RECORD TIME | cas TO nnn KMH
cas = CHANGE AVERAGE SPEED | CAS
*/

};

int is_number(const string &s) {
	for (int i = 0; i < (int)s.size(); i++)
		if (!isdigit(s[i])) return 0;
	return 1;
}

int check(const VS &v, char *line) {
	VS t;

	if (strstr(line, "\"\"") != NULL) return 1;
	if (strstr(line, " .") != NULL) return 1;

	for (int i = 0; i < (int)v.size(); i++) {
		const string &s = v[i];

		for (int j = 0; j < (int)s.size(); j++) {
			int c = s[j];
			if (c == '\"' || c == '.' || c == ' ') continue;
			if (isupper(c) || isdigit(c)) continue;
			return 1;
		}

		if (s[0] == '\"') {
			if (s.size() < 3 || s[s.size()-1] != '\"') return 1;
			if (s[1] == ' ') return 1;
			if (s[s.size()-2] == ' ') return 1;
			for (int i = 1; i+1 < (int)s.size(); i++)
				if (!isupper(s[i]) && s[i] != ' ' && s[i] != '.')
					return 1;
			t.push_back("quoted");
		} else if (is_number(s)) {
			t.push_back("number");
		} else if (s == "quoted" || s == "number") {
			return 1;
		} else {
			t.push_back(s);
		}
	}
	return Grammar(t).ins() == 0;
}

int main()
{
	char line[65536];
	for (int cs = 1; gets(line) && strcmp(line, "#") != 0; cs++) {
		VS v = tokenize(line);
		if (check(v, line)) {
			printf("%3d. Trap!\n", cs);
		} else {
			printf("%3d.", cs);
			for (int i = 0; i < v.size(); i++)
				printf(" %s", v[i].c_str());
			printf("\n");
		}
	}
}
