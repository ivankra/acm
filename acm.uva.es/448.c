#include <stdio.h>

static int next()
{
	register int c;

	while ((c = getchar()) != EOF)
		if (c >= '0' && c <= '9')
			return (c - '0');
		else if (c >= 'A' && c <= 'F')
			return (c - 'A' + 10);
		else if (c >= 'a' && c <= 'f')
			return (c - 'a' + 10);

	return -1;
}

int main()
{
	char *s[16] = { "ADD", "SUB", "MUL", "DIV", "MOV", "BREQ", "BRLE",
			"BRLS", "BRGE", "BRGR", "BRNE", "BR", "AND", "OR",
			"XOR", "NOT" };
	int n[16] = { 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 1 };
	int c, v, i, r;

	while ((c = next()) >= 0) {
		printf("%s ", s[c]);

		for (r = n[c]; r-- > 0;) {
			for (i = 0, v = 0; i < 4 && (c = next()) >= 0; i++)
				v = (v << 4) | c;

			c = (v >> 14) & 3;
			v &= 0x3FFF;

			if (c == 0)
				printf("R%d", v);
			else if (c == 1)
				printf("$%d", v);
			else if (c == 2)
				printf("PC+%d", v);
			else
				printf("%d", v);

			if (r != 0)
				printf(",");
		}

		printf("\n");
	}

	return 0;
}
