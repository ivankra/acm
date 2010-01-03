#include <cstdio>
#include <cctype>
#include <cstring>
#include <cassert>

char line[1024], *tok;
int var[32], prev[32], size;
struct Node { int left, right, type, val, lval; } tree[1024];

void ws() { while (*tok && isspace(*tok)) tok++; }

int node(int t, int l=0, int r=0) {
	size++;
	tree[size].type = t;
	tree[size].left = l;
	tree[size].right = r;
	return size;
}

int expr();

int fact() {
	ws();
	if (isalpha(*tok)) return node(toupper(*tok++));
	if (*tok == '_') { tok++; return node('-', node('n',0), fact()); }
	if (*tok == '(') {
		tok++;
		int x = expr();
		ws();
		if (*tok == ')') tok++;
		return x;
	}

	int p = 0, x;
	sscanf(tok, "%d %n", &x, &p);
	tok += p;
	return node('n', x);
}

int expr() {
	int l = fact();
	ws();
	int op = *tok;
	if (op == 0 || strchr("+-*/=", op) == NULL) {
		return l;
	} else {
		tok++;
		return node(op, l, expr());
	}
}

int eval(int r) {
	Node &n = tree[r];
	n.lval = -1;
	if (isupper(n.type)) {
		n.lval = n.type - 'A';
		n.val = var[n.lval];
	} else if (n.type == 'n') {
		n.val = n.left;
	} else if (n.type == '+') {
		n.val = eval(n.right);
		n.val += eval(n.left);
	} else if (n.type == '-') {
		n.val = -eval(n.right);
		n.val += eval(n.left);
	} else if (n.type == '*') {
		n.val = eval(n.right);
		n.val *= eval(n.left);
	} else if (n.type == '/') {
		n.val = eval(n.right);
		assert(n.val != 0);
		n.val = eval(n.left) / n.val;
	} else if (n.type == '=') {
		n.val = eval(n.right);
		eval(n.left);
		n.lval = tree[n.left].lval;
		assert(n.lval >= 0);
		var[n.lval] = n.val;
	}
	return n.val;
}

int main()
{
	memset(var, 0, sizeof(var));
	while (gets(line) && strchr(line, '#') == NULL) {
		memcpy(prev, var, sizeof(var));
		tok = line;
		size = 0;
		eval(expr());
		int k = 0;
		for (int i = 0; i < 26; i++)
			if (prev[i] != var[i])
				printf("%s%c = %d", k++ ? ", " : "", i+'A', var[i]);
		printf(k ? "\n" : "No Change\n");
	}
}
