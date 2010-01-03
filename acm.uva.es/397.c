#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXN 128

int left[MAXN], right[MAXN], op[MAXN], val[MAXN], count, la, numeric;
char name[256];

int next()
{
	int i, c;

	for (;;) {
		c = getchar();
		if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
			continue;

		if (c == EOF) {
			return (la = 0);
		} else if (c=='+' || c=='-' || c=='*' || c=='/' || c=='=') {
			return (la = c);
		} else if (c >= '0' && c <= '9') {
			ungetc(c, stdin);
			scanf("%d", &numeric);
			return (la = 'n');
		}

		for (i = 0; i < (sizeof(name) - 1) && isalpha(c);) {
			name[i++] = c;
			c = getchar();
		}

		if (i != 0) {
			if (c != EOF) ungetc(c, stdin);
			name[i] = '\0';
			return (la = 'v');
		}
	}
}

int fact()
{
	int s;

	for (s = 0; la == '-' || la == '+';) {
		if (la == '-') s = !s;
		next();
	}

	if (la != 'n')
		return -1;

	op[count] = 'n';
	val[count] = s ? -numeric : numeric;
	next();

	return count++;
}

int term()
{
	int n = fact();
	while (la == '*' || la == '/') {
		op[count] = la;
		left[count] = n;
		n = count++;
		next();
		right[n] = fact();
	}
	return n;
}

int expr()
{
	int n = term();
	while (la == '+' || la == '-') {
		op[count] = la;
		left[count] = n;
		n = count++;
		next();
		right[n] = term();
	}
	return n;
}

void print(int n)
{
	while (n >= 0) {
		if (op[n] == 'n') {
			printf("%d ", val[n]);
			break;
		} else if (op[n]=='+' || op[n]=='-' || op[n]=='*' || op[n]=='/') {
			print(left[n]);
			printf("%c ", op[n]);
			n = right[n];
		} else {
			break;
		}
	}
}

int simplify(int n)
{
	static int q[MAXN];
	int i, k;

	q[0] = n;
	for (n = -1, k = 1; k > 0;) {
		i = q[--k];
		if (op[i] == 'n') {
			continue;
		} else if (op[left[i]] == 'n' && op[right[i]] == 'n') {
			if (n < 0) n = i;
			if (op[i] == '*' || op[i] == '/') {
				n = i;
				break;
			}
		} else {
			q[k++] = right[i];
			q[k++] = left[i];
		}
	}

	if (n < 0)
		return 0;

	if (op[n] == '+')
		val[n] = val[left[n]] + val[right[n]];
	else if (op[n] == '-')
		val[n] = val[left[n]] - val[right[n]];
	else if (op[n] == '*')
		val[n] = val[left[n]] * val[right[n]];
	else if (op[n] == '/')
		val[n] = val[left[n]] / val[right[n]];
	op[n] = 'n';
	return 1;
}

int main()
{
	int root;

	for (count = 0; next() && (root = expr()) >= 0; count = 0) {
		if (la == '=') next();
		if (la != 'v') continue;

		do {
			print(root);
			printf("= %s\n", name);
		} while (simplify(root));

		printf("\n");
	}

	return 0;
}
