#include <cstdio>
#include <cstring>
#include <cctype>

int tok;
char token[1024];

int next() {
	int nl = 0;
	for (;;) {
		int c = getchar();
		if (c == EOF) return tok = EOF;

		if (c == '\r') continue;
		if (c == '\n') {
		       if (++nl >= 2) return tok = '\n';
		       continue;
		}
		nl = 0;

		if (isspace(c)) continue;

		if (strchr("+();,", c) != NULL) {
			sprintf(token, "%c", c);
			return tok = 't';
		}

		if (c == '-') {
			c = getchar();
			if (c != '-') {
				ungetc(c, stdin);
				sprintf(token, "-");
				return tok = 't';
			}

			while ((c = getchar()) != EOF && c != '\n');
			if (c != EOF) ungetc(c, stdin);

			continue;
		}

		if (c == ':') {
			c = getchar();
			if (c != '=') {
				ungetc(c, stdin);
				return tok = 'e';
			}
			sprintf(token, ":=");
			return tok = 't';
		}

		if (isalnum(c) || c=='_') {
			int n = 0;
			while (isalnum(c) || c == '_') {
				if (n >= 32) return tok = 'e';
				token[n++] = c;
				c = getchar();
			}
			ungetc(c, stdin);
			token[n] = 0;

			int alldig = 1;
			for (int i = 0; i < n; i++)
				if (!isdigit(token[i])) { alldig = 0; break; }
			if (alldig && n > 8) return tok = 'e';

			return tok='t';
		}

		return tok='e';
	}
}

int main() {
	for (;;) {
		for (;;) {
			next();

			if (tok == 'e') {
				printf("TOKEN ERROR\n");
				while (tok!='\n' && tok!=EOF) next();
				break;
			}

			if (tok == '\n' || tok == EOF) break;

			printf("%s\n", token);
		}

		if (tok == EOF) break;
		printf("\n");
	}
}
