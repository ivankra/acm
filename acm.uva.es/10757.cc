#include <cstdio>
#include <cctype>
#include <cassert>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

static int GE = 1001, LE = 1002, NE = 1003;
static int tok, tok_n;
static char tok_s[500000];

void assert1(bool x) {
	if (x == false) { for(;;); }
}

int strcasecmp(const char *s, const char *t) {
	while (*s != 0 && *t != 0) {
		if (toupper(*s) != toupper(*t)) return toupper(*s) < toupper(*t) ? -1 : 1;
		s++; t++;
	}
	if (*s == 0 && *t == 0) return 0;
	return toupper(*s) < toupper(*t) ? -1 : 1;
}

int next() {
	for (;;) {
		int c = getchar();
		if (c == EOF) return tok = EOF;

		if (isspace(c)) continue;

		if (isalpha(c)) {
			int i;
			for (i = 0; c != EOF && isalnum(c);) {
				tok_s[i++] = c;
				c = getchar();
			}
			tok_s[i] = 0;
			if (c != EOF) ungetc(c, stdin);
			return tok = 'a';
		}

		if (c == '+' || c == '-' || isdigit(c)) {
			int i = 0;
			if (c == '+' || c == '-') {
				tok_s[i++] = c;
				c = getchar();
			}

			assert(isdigit(c));

			while (c != EOF && isdigit(c)) {
				tok_s[i++] = c;
				c = getchar();
			}
			if (c != EOF) ungetc(c, stdin);
			tok_s[i] = 0;

			tok_n = atoi(tok_s);
			return tok = 'n';
		}

		if (c == '\"') {
			int i = 0;
			c = getchar();
			while (c != '\"') {
				assert(c != '\n');
				if (c == '\\') {
					c = getchar();
					assert(c == '\\' || c == '\"');
				}
				tok_s[i++] = c;
				c = getchar();
				assert(c != EOF);
			}
			tok_s[i] = 0;
			return tok = 's';
		}

		if (strchr("*,()=", c) != NULL)
			return tok = c;

		if (c == '<' || c == '>') {
			int c1 = getchar();
			if (c1 == '=') return tok = (c == '<' ? LE : GE);
			if (c == '<' && c1 == '>') return tok = NE;
			if (c1 != EOF) ungetc(c1, stdin);
			return tok = c;
		}

		assert(false);
	}
}

int nextint() {
	assert(tok == 'n');
	int n = tok_n;
	next();
	return n;
}

void skip(const char *kw) {
	assert(tok == 'a' && strcasecmp(tok_s, kw) == 0);
	next();
}

int compare(const string &s1, const string &s2, int type) {
	if (type == 'I') {
		int a = atoi(s1.c_str());
		int b = atoi(s2.c_str());
		if (a == b) return 0;
		return a < b ? -1 : 1;
	} else {
		return s1.compare(s2);
	}
}

struct ColumnDesc {
	string name;
	int type;
};

struct Table {
	string name;
	int nrows, ncols;
	vector<ColumnDesc> col;
	vector< vector<string> > data;

	int columnByName(const char *s) const {
		for (int i = 0; i < ncols; i++)
			if (strcasecmp(col[i].name.c_str(), s) == 0) return i;
		assert(false);
	}
};

class ByColumn {
	const Table *t;
	int c;

public:
	ByColumn(const Table *T, int C) : t(T), c(C) {}

	bool operator()(int i1, int i2) const {
		int res = compare(t->data[i1][c], t->data[i2][c], t->col[c].type);
		if (res == 0) return i1 < i2;
		return res < 0;
	}
};

struct OrderBy {
	vector<int> col, dir;
	Table *tab;

	bool operator()(int r1, int r2) const {
		for (int i = 0; i < (int)col.size(); i++) {
			int c = col[i];
			int res = dir[i] * compare(tab->data[r1][c], tab->data[r2][c], tab->col[c].type);
			if (res != 0) return res < 0;
		}
		return r1 < r2;
	}
};

struct Where {
	int op;
	string value;
	Where *left, *right;

	int tmp;

	Where(int o, const char *s, Where *l = NULL, Where *r = NULL) :
	op(o), value(s), left(l), right(r), tmp(-1) {}

	~Where() {
		if (left != NULL) delete left;
		if (right != NULL) delete right;
	}
};

class WhereEvaluator {
	Table *tab;
	Where *root;
	int row;

	void eval2(Where *w, string &s, int &type) {
		if (w->op == 'n' || w->op == 's') {
			s = w->value;
			type = (w->op == 'n' ? 'I' : 'S');
		} else {
			if (w->tmp == -1)
				w->tmp = tab->columnByName(w->value.c_str());
			s = tab->data[row][w->tmp];
			type = tab->col[w->tmp].type;
		}
	}

	bool eval(Where *w) {
		if (w == NULL) return true;

		if (w->op == '!') return !eval(w->left);
		if (w->op == '&') return eval(w->left) && eval(w->right);
		if (w->op == '|') return eval(w->left) || eval(w->right);

		string s1, s2;
		int type1, type2;
		eval2(w->left, s1, type1);
		eval2(w->right, s2, type2);

		assert(type1 == type2);

		if (w->op == '<') return compare(s1, s2, type1) < 0;
		if (w->op == '>') return compare(s1, s2, type1) > 0;
		if (w->op == '=') return compare(s1, s2, type1) == 0;
		if (w->op == LE) return compare(s1, s2, type1) <= 0;
		if (w->op == GE) return compare(s1, s2, type1) >= 0;
		if (w->op == NE) return compare(s1, s2, type1) != 0;
		assert(false);
	}
public:
	WhereEvaluator(Table *t, Where *w) : tab(t), root(w) {}

	bool evaluate(int r) {
		row = r;
		return eval(root);
	}
};

vector<Table> tables;
vector<Table *> tmp_tables;

void dumpTable(const Table &t) {
	for (int i = 0; i < t.ncols; i++)
		printf("%10s", t.col[i].name.c_str());
	printf("\n");

	for (int i = 0; i < t.nrows; i++) {
		for (int j = 0; j < t.ncols; j++)
			printf("%10s", t.data[i][j].c_str());
		printf("\n");
	}
	printf("\n");
}

void readTables() {
	int ntables = nextint();
	assert(ntables <= 30);

	tables.clear();
	tables.resize(ntables);

	for (int ti = 0; ti < ntables; ti++) {
		Table &t = tables[ti];

		assert(tok == 'a');
		t.name = string(tok_s);
		next();

		assert(tok == 'n');
		t.ncols = tok_n;
		next();
		assert(1 <= t.ncols && t.ncols <= 10);

		assert(tok == 'n');
		t.nrows = tok_n;

		t.col.resize(t.ncols);

		for (int i = 0; i < t.ncols; i++) {
			assert(next() == 'a');
			t.col[i].name = string(tok_s);

			assert(next() == 'a');
			tok_s[0] = toupper(tok_s[0]);
			t.col[i].type = tok_s[0];
			assert(strlen(tok_s) == 1 && (tok_s[0] == 'I' || tok_s[0] == 'S'));
		}

		t.data.clear();
		t.data.assign(t.nrows, vector<string>(t.ncols));

		for (int i = 0; i < t.nrows; i++) {
			for (int j = 0; j < t.ncols; j++) {
				scanf(" %s", tok_s);
				t.data[i][j] = string(tok_s);					
			}
		}

		next();
	}
}

Table *parseFrom() {
	Table *A = NULL;

	if (tok == '(') {
		next();
		A = parseFrom();
		assert(tok == ')');
		next();
	} else {
		assert(tok == 'a');
		for (int i = 0; i < (int)tables.size(); i++) {
			if (strcasecmp(tables[i].name.c_str(), tok_s) == 0) {
				A = &tables[i];
				break;
			}
		}
		next();
	}
	assert(A != NULL);

	for (;;) {
		if (tok != 'a' || strcasecmp(tok_s, "INNER") != 0) return A;

		skip("INNER");
		skip("JOIN");

		Table *B = parseFrom();

		skip("ON");

		assert(tok == 'a');
		int col1 = A->columnByName(tok_s);
		next();

		assert(tok == '=');
		next();

		assert(tok == 'a');
		int col2 = B->columnByName(tok_s);
		next();

		assert(A->col[col1].type == B->col[col2].type);
		int coltype = A->col[col1].type;

		Table *C = new Table();
		tmp_tables.push_back(C);

		C->name = "";
		C->nrows = 0;
		C->ncols = A->ncols + B->ncols;
		C->col = A->col;
		for (int i = 0; i < B->ncols; i++)
			C->col.push_back(B->col[i]);
		C->data.clear();

		vector<int> o1(A->nrows), o2(B->nrows);
		for (int i = 0; i < A->nrows; i++) o1[i] = i;
		for (int i = 0; i < B->nrows; i++) o2[i] = i;

		sort(o1.begin(), o1.end(), ByColumn(A, col1));
		sort(o2.begin(), o2.end(), ByColumn(B, col2));

		int posA = 0, posB = 0;
		vector<long long> pairs;

		while (posA < A->nrows && posB < B->nrows) {
			int res = compare(A->data[o1[posA]][col1], B->data[o2[posB]][col2], coltype);
			if (res != 0) {
				if (res < 0) posA++; else posB++;
				continue;
			}

			int p, q;
			for (p = posA; p < A->nrows; p++) {
				if (compare(A->data[o1[posA]][col1], A->data[o1[p]][col1], coltype) != 0)
					break;
			}

			for (q = posB; q < B->nrows; q++) {
				if (compare(A->data[o1[posA]][col1], B->data[o2[q]][col2], coltype) != 0)
					break;
			}

			for (int i = posA; i < p; i++)
				for (int j = posB; j < q; j++)
					pairs.push_back((((long long)o1[i])<<32) | o2[j]);

			posA = p;
			posB = q;
		}

		sort(pairs.begin(), pairs.end());

		for (int k = 0; k < (int)pairs.size(); k++) {
			int r1 = pairs[k] >> 32;
			int r2 = pairs[k] & 0xffffffff;

			C->data.push_back(A->data[r1]);
			for (int i = 0; i < B->ncols; i++)
				C->data.back().push_back(B->data[r2][i]);
			C->nrows++;
		}

		A = C;
	}
}

Table *parseFromClause() {
	skip("FROM");
	tmp_tables.clear();
	return parseFrom();
}

Where *parseWhere();

Where *parseWhere2() {
	if (tok == '(') {
		next();
		Where *res = parseWhere();
		assert(tok == ')');
		next();
		return res;
	}

	char ch;
	scanf(" %c", &ch);
	ungetc(ch, stdin);

	if (tok == 'a' && strcasecmp(tok_s, "NOT") == 0 && strchr("<>=", ch) == NULL) {
		next();
		return new Where('!', "", parseWhere2());
	}

	assert(tok == 'a' || tok == 's' || tok == 'n');
	Where *l = new Where(tok, tok_s);
	next();

	assert(tok == '=' || tok == LE || tok == GE || tok == NE || tok == '<' || tok == '>');
	int op = tok;
	next();

	assert(tok == 'a' || tok == 's' || tok == 'n');
	Where *r = new Where(tok, tok_s);
	next();

	return new Where(op, "", l, r);
}

Where *parseWhere() {
	Where *res = parseWhere2();
	while (tok == 'a') {
		if (strcasecmp(tok_s, "AND") == 0) {
			next();
			res = new Where('&', "", res, parseWhere2());
		} else if (strcasecmp(tok_s, "OR") == 0) {
			next();
			res = new Where('|', "", res, parseWhere2());
		} else {
			break;
		}
	}
	return res;
}

Where *parseWhereClause() {
	if (tok != 'a' || strcasecmp(tok_s, "WHERE") != 0) return NULL;
	skip("WHERE");

	return parseWhere();
}

void solveQuery() {
	skip("SELECT");

	vector<string> selnames;
	if (tok == '*') {
		next();
	} else {
		for (;;) {
			assert(tok == 'a');
			selnames.push_back(tok_s);
			next();
			if (tok != ',') break;
			next();
		}
	}

	Table *from = parseFromClause();
	Where *where = parseWhereClause();
	WhereEvaluator where_eval(from, where);

//	dumpTable(*from);

	vector<int> sel;
	if (selnames.size() == 0) {
		for (int i = 0; i < (int)from->ncols; i++) {
			sel.push_back(i);
			selnames.push_back(from->col[i].name);
		}
	} else {
		for (int i = 0; i < (int)selnames.size(); i++) {
			sel.push_back(from->columnByName(selnames[i].c_str()));
		}
	}

	OrderBy order;
	order.tab = from;
	order.col.clear();
	order.dir.clear();

	if (tok == 'a' && strcasecmp(tok_s, "ORDER") == 0) {
		skip("ORDER");
		skip("BY");

		for (;;) {
			assert(tok == 'a');
			order.col.push_back(from->columnByName(tok_s));
			next();

			if (tok == 'a' && strcasecmp(tok_s, "ASCENDING") == 0) {
				order.dir.push_back(1);
				next();
			} else if (tok == 'a' && strcasecmp(tok_s, "DESCENDING") == 0) {
				order.dir.push_back(-1);
				next();
			} else {
				order.dir.push_back(1);
			}

			if (tok != ',') break;
			next();
		}
	}

	vector<int> rows;
	for (int i = 0; i < from->nrows; i++)
		if (where_eval.evaluate(i)) rows.push_back(i);

	sort(rows.begin(), rows.end(), order);

	printf("%d %d\n", sel.size(), rows.size());
	for (int i = 0; i < (int)sel.size(); i++) {
//		printf("%s\n", selnames[i].c_str());
		printf("%s\n", from->col[sel[i]].name.c_str());

	}

	for (int i = 0; i < (int)rows.size(); i++) {
		int r = rows[i];
		for (int j = 0; j < (int)sel.size(); j++) {
			printf(j==0 ? "%s" : " %s", from->data[r][sel[j]].c_str());
		}
		printf("\n");
	}

	if (where != NULL) delete where;

	for (int i = 0; i < (int)tmp_tables.size(); i++)
		delete tmp_tables[i];
	tmp_tables.clear();
}

int main()
{
	next();
	int T = nextint();

	for (int cs = 1; cs <= T; cs++) {
		readTables();
		solveQuery();
		if (cs < T) printf("\n");
	}
}
