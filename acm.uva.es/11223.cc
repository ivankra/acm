#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

char *codes[] = {
"A.-",
"B-...",
"C-.-.",
"D-..",
"E.",
"F..-.",
"G--.",
"H....",
"I..",
"J.---",
"K-.-",
"L.-..",
"M--",
"N-.",
"O---",
"P.--.",
"Q--.-",
"R.-.",
"S...",
"T-",
"U..-",
"V...-",
"W.--",
"X-..-",
"Y-.--",
"Z--..",
"0-----",
"1.----",
"2..---",
"3...--",
"4....-",
"5.....",
"6-....",
"7--...",
"8---..",
"9----.",
"..-.-.-",
",--..--",
"?..--..",
"'.----.",
"!-.-.--",
"/-..-.",
"(-.--.",
")-.--.-",
"&.-...",
":---...",
";-.-.-.",
"=-...-",
"+.-.-.",
"--....-",
"_..--.-",
"\".-..-.",
"@.--.-.",
NULL
};

int main() {
	char line[50000];
	int T;

	gets(line);
	sscanf(line, "%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		if (cs != 1) printf("\n");
		printf("Message #%d\n", cs);

		gets(line);
		for (int i = 0; line[i] && line[i] != '\r' && line[i] != '\n';) {
			if (line[i] == ' ' && line[i+1] == ' ') {
				putchar(' ');
				i += 2;
				continue;
			}

			if (line[i] != '.' && line[i] != '-') { i++; continue; }

			char *p = line + i;
			while (line[i] == '.' || line[i] == '-') i++;

			char ch = line[i];
			line[i] = 0;

			for (int k = 0; ; k++) {
				assert(codes[k] != NULL);
				if (strcmp(codes[k]+1, p) == 0) {
					putchar(codes[k][0]);
					break;
				}
			}

			line[i] = ch;
		}
		printf("\n");
	}
}
