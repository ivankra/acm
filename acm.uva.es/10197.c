#include <stdio.h>

int main()
{
	static char v1[256], v2[256], lwr[256], sufv[256];
	static char *suf[6][3] = {
		{ "o", "o", "o" },
		{ "as", "es", "es" },
		{ "a", "e", "e" },
		{ "amos", "emos", "imos" },
		{ "ais", "eis", "is" },
		{ "am", "em", "em" }
	};
	int i, m, t;

	for (i = 0; i < 256; i++)
		lwr[i] = (i >= 'A' && i <= 'Z') ? (i - 'A' + 'a') : i;

	for (i = 0; i < 256; i++)
		sufv[i] = (lwr[i] == 'a' ? 0 :
			   (lwr[i] == 'e' ? 1 :
			    (lwr[i] == 'i' ? 2 : -1)));

	for (t = 0; scanf(" %255[a-zA-Z] %255[a-zA-Z]", v1, v2) == 2; t++) {
		printf("%s%s (to %s)\n", (t > 0) ? "\n" : "", v1, v2);

		for (m = 0; v1[m]; m++);

		if (m < 2 || lwr[v1[m - 1]] != 'r' || sufv[v1[m - 2]] < 0) {
			printf("Unknown conjugation\n");
			continue;
		}

		i = sufv[v1[m - 2]];
		v1[m - 2] = '\0';

		printf(	"eu        %s%s\n"
			"tu        %s%s\n"
			"ele/ela   %s%s\n"
			"n%cs       %s%s\n"
			"v%cs       %s%s\n"
			"eles/elas %s%s\n",

			v1, suf[0][i],
			v1, suf[1][i],
			v1, suf[2][i],
			243, v1, suf[3][i],
			243, v1, suf[4][i],
			v1, suf[5][i]);
	}

	return 0;
}
