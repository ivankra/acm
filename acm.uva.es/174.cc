#include <cstdio>
#include <cstring>
#include <cctype>
#include <cassert>

struct Node {
	char *what, *c_rhs;
	Node *a, *b, *c;
	int c_my, c_last, c_eq;
	Node(char *S, Node *A=NULL, Node *B=NULL, Node *C=NULL) :
		what(S), a(A), b(B), c(C) {}
};

struct Parser {
	char *p;
	Parser(char *src) : p(src) {}

	int eq(char *word) {
		if (memcmp(p, word, strlen(word)) != 0) return 0;
		p += strlen(word);
		return 1;
	}

	Node *cond() {
		Node *z = new Node("COND");

		if (eq("MYLAST")) z->c_my = 1;
		else if (eq("YOURLAST")) z->c_my = 0;
		else assert(0 == 1);

		assert(isdigit(*p));
		z->c_last = *p++ - '0';

		assert(*p == '=' || *p == '#');
		z->c_eq = (*p++ == '=');

		if (eq("TRADE")) z->c_rhs = "TRADE";
		else if (eq("CHEAT")) z->c_rhs = "CHEAT";
		else if (eq("NULL")) z->c_rhs = "NULL";
		else assert(0==1);

		if (eq("AND")) return new Node("AND", z, cond());
		if (eq("OR")) return new Node("OR", z, cond());
		return z;
	}

	Node *stmt() {
		if (eq("TRADE")) return new Node("TRADE");
		if (eq("CHEAT")) return new Node("CHEAT");
		if (!eq("IF")) assert(0==1);
		Node *c = cond();
		if (!eq("THEN")) assert(0==1);
		Node *a = stmt();
		if (!eq("ELSE")) assert(0==1);
		return new Node("IF", c, a, stmt());
	}
};

struct Strategy {
	int score;
	char source[512], *last[3];
	Node *node;
};

int evalBool(Strategy &A, Strategy &B, Node *x) {
	if (strcmp(x->what, "AND") == 0)
		return evalBool(A,B,x->a) && evalBool(A,B,x->b);

	if (strcmp(x->what, "OR") == 0)
		return evalBool(A,B,x->a) || evalBool(A,B,x->b);

	char *lhs = x->c_my ? A.last[x->c_last] : B.last[x->c_last];
	return strcmp(lhs, x->c_rhs) == 0 ? x->c_eq : !x->c_eq;
}

char *eval(Strategy &A, Strategy &B, Node *x) {
	for (;;) {
		if (strcmp(x->what, "TRADE")==0 || strcmp(x->what, "CHEAT")==0)
			return x->what;
		x = evalBool(A,B,x->a) ? x->b : x->c;
	}
}

void play(Strategy &A, Strategy &B) {
	for (int k = 1; k <= 2; k++)
		A.last[k] = B.last[k] = "NULL";

	for (int k = 0; k < 10; k++) {
		char *a = eval(A, B, A.node);
		char *b = eval(B, A, B.node);

		if (strcmp(a, "TRADE") == 0) {
			if (strcmp(b, "TRADE") == 0)
				A.score++, B.score++;
			else
				{ A.score -= 2; B.score += 2; }
		} else {
			if (strcmp(b, "TRADE") == 0)
				{ A.score += 2; B.score -= 2; }
			else
				A.score--, B.score--;
		}

		A.last[2] = A.last[1]; A.last[1] = a;
		B.last[2] = B.last[1]; B.last[1] = b;
	}
}

int main()
{
	Strategy S[16];
	int n;

	memset(S, 0, sizeof(S));
	for (n = 0;; n++) {
		int k=0, c;
		while ((c = getchar()) != EOF) {
			if (isspace(c)) continue;
			if (k == 0 && c == '#') break;
			S[n].source[k++] = toupper(c);
			if (c == '.') break;
		}
		S[n].source[k] = 0;
		if (k == 0) break;
		S[n].node = Parser(S[n].source).stmt();
		S[n].score = 0;
	}

	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++)
			play(S[i], S[j]);

	for (int i = 0; i < n; i++)
		printf("%3d\n", S[i].score);
}
