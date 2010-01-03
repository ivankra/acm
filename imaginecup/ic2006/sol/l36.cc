#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vector>
#include <string>
#include <algorithm>
#define foreach(i,v) for(__typeof((v).begin())i=(v).begin();i!=(v).end();i++)
using namespace std;
typedef vector<char *> VC;
typedef vector<VC> VVC;

/****************************************************************************/
/* Herbert: interpreter of h language */

#define HMEM 131072
struct Herbert {
	/*
	 *  re = pointer to next command to be executed
         *  rs = stack pointer
         *  rf = frame pointer
         */
	char *mem, *re, *rs, *err;
	struct Frame { char *pe; struct Frame *pf; } *rf;

	struct {
		int def, n, which[32];  /* 0=A, 1=B, ... */
		char *code;
	} ftab[32];  /* 0=main, 1=a, 2=b, ... */

	Herbert() { mem = (char *)malloc(HMEM); }
	~Herbert() { free(mem); }

	int load(const char *);
	int next(int);
};

/*
 *  Executes herbert program until:
 *    * one of 's', 'l', or 'r' commands is executed ('s','l','r' is returned)
 *    * program terminates (0 is returned)
 *    * an error occurs (-1 is returned)
 *    * 'limit' operations are performed (-2 is returned)
 *      (an operation is a procedure call or exit.)
 */
int Herbert::next(int limit) {
	err = NULL;
	while (limit-- > 0) {
		if (*re == '\0') {
			/* end of current procedure */
			if (rf->pf == NULL) return 0;
			re = rf->pe;
			rs = (char *)rf;
			rf = rf->pf;
			continue;
		}

		if (*re == 's' || *re == 'l' || *re == 'r')
			return *re++;

		if (!islower(*re)) { err = "Invalid command"; return -1; }

		int f = *re - 'a' + 1;
		re++;
		if (!ftab[f].def) { err = "Undefined function"; return -1; }

                /* the program calls procedure f */

		struct Frame *fp = (struct Frame *)rs;
		rs += sizeof(struct Frame);
		if (rs > mem+HMEM-16) { err = "Out of memory"; return -1; }

		if (*re != '(' || (ftab[f].n == 0 && re[0] == '(' && re[1] == ')')) {
			/* A parameter-less function */
			if (*re == '(') re += 2;
			if (ftab[f].n > 0) { err = "Too few parameters"; return -1; }
			fp->pe = re;
			fp->pf = rf;
			rf = fp;
			re = ftab[f].code;
			continue;
		}
		re++;

		char *arg[32], stop = 0;
		int narg = ftab[f].n;

		for (int i = 0; i < narg; i++) {
			if (i > 0) {
				if (*re != ',') { err = "Syntax error"; return -1; }
				re++;
			}
			if (*re == ')') { err = "Too few parameters"; return -1; }

			if (isdigit(*re) || *re == '+' || *re == '-') {
				/* numeric parameter */
				int z, x, y;
				for (z = 0; sscanf(re, " %d %n", &x, &y) >= 1; re += y)
					z += x;
				if (z < -256 || z > 255) {
					err = "Numeric overflow";
					return -1;
				}
				if (z <= 0) stop = 1;
				if (stop) continue;
				if (rs > mem+HMEM-16) {
					err = "Out of memory";
					return -1;
				}
				arg[i] = rs;
				rs += sprintf(rs, "%d", z) + 1;
			} else {
				/* procedure parameter */
				arg[i] = rs;
				for (int b = 0;; re++) {
					if (*re == '\0') {
						err = "Syntax error";
						return -1;
					}
					if (b == 0 && (*re == ',' || *re == ')')) break;
					if (*re == '(') b++;
					if (*re == ')') b--;
					if (stop) continue;
					if (rs > mem+HMEM-16) {
						err = "Out of memory";
						return -1;
					}
                                        *rs++ = *re;
				}
				if (stop) continue;
                                *rs++ = '\0';
			}
		}

		if (*re != ')') { err = "Syntax error, or too many parameters"; return -1; }
		re++;

		if (stop) {
			/* one of numeric parameters evaluated to zero or
			   a negative integer, procedure will not be called */
			rs = (char *)fp;
			continue;
		}

		fp->pe = re;
		fp->pf = rf;

		rf = fp;
		re = rs;
		for (char *p = ftab[f].code; *p; p++) {
			if (rs > mem+HMEM-16) { err = "Out of memory"; return -1; }
			if (!isupper(*p)) { *rs++ = *p; continue; }

			if (ftab[f].which[*p-'A'] < 0) { err = "Undeclared parameter"; return -1; }

			for (char *q = arg[ftab[f].which[*p-'A']]; *q;) {
				if (rs > mem+HMEM-16) {
					err = "Out of memory";
					return -1;
				}
				*rs++ = *q++;
			}
		}
                *rs++ = '\0';
	}
	err = "Operations limit exceeded";
	return -2;
}

int Herbert::load(const char *s) {
	for (int i = 0; i <= 26; i++) {
		ftab[i].def = 0;
		ftab[i].code = NULL;
		for (int j = 0; j < 26; j++) ftab[i].which[j] = -1;
	}
	rs = mem;
	err = NULL;

	if (strlen(s) > HMEM-1024) { err = "Too long program"; return 1; }

	for (;;) {
		while (*s && (isspace(*s) || *s == '\n' || *s == '\r')) s++;
		if (*s == '\0') break;

		const char *e;
		int f = 0;

		for (e = s; *e && *e != '\n' && *e != '\r'; e++)
			if (*e == ':') f = -1;

		err = "Syntax error";
		if (f == 0) {
			if (ftab[0].def) { err = "Multiple execution lines"; return 1; }
			ftab[0].n = 0;
		} else {
			if (!islower(*s)) return 1;
			f = *s++ - 'a' + 1;
			ftab[f].n = 0;
			if (*s == '(') {
				for (s++; isupper(*s); ftab[f].n++) {
					if (ftab[f].n > 15) {
						err = "Too many parameters";
						return 1;
					}
					if (ftab[f].which[*s-'A'] >= 0) {
						err = "Repeating parameter name";
						return 1;
					}
					ftab[f].which[*s-'A'] = ftab[f].n;
					s++;
					if (*s == ',') s++;
				}
				if (*s != ')') return 1;
				s++;
			}
			if (*s != ':') return 1;
			s++;
		}

		ftab[f].def = 1;
		for (ftab[f].code = rs; s < e; s++)
			if (!isspace(*s)) *rs++ = *s;
                *rs++ = '\0';
	}

	if (!ftab[0].def) { err = "No execution line"; return 1; }

	rf = (struct Frame *)rs;
	rs += sizeof(struct Frame);
	rf->pe = NULL;
	rf->pf = NULL;
	re = ftab[0].code;
	err = NULL;
	return 0;
}

/****************************************************************************/
/* Scene: represents the level's map and processes Herbert's movements in it */

struct Scene {
	char grid[32][32];
	int seen[32][32], seen_id, pwhite, nwhite, solved;
	int hx, hy, hd, init_hy, init_hx, init_hd;
	int pgray;

	void exec(int c) {
		static int dx[] = { 0, 1, 0, -1 };
		static int dy[] = { -1, 0, 1, 0 };
		if (c == 'l') { hd = (hd + 3) & 3; return; }
		if (c == 'r') { hd = (hd + 1) & 3; return; }
		c = grid[hy+dy[hd]][hx+dx[hd]];
		if (c == '#') return;
		hy += dy[hd]; hx += dx[hd];
		if (c == 'o') {
			if (seen[hy][hx] < seen_id) {
				pwhite++;
				seen[hy][hx] = seen_id;
				solved = (pwhite == nwhite);
			}
		} else if (c == '*') {
			pgray++;
			seen_id++;
			pwhite = 0;
			solved = (nwhite == 0);
		}
	}

	int load(const char *filename) {
		printf("Loading level: '%s'\n", filename);

		FILE *fp = filename ? fopen(filename, "r") : stdin;
		if (fp == NULL) return 1;

		memset(grid, '#', sizeof(grid));
		init_hd = -1;
		nwhite = 0;
		for (int row = 1; row <= 25; row++) {
			for (int col = 1, c; col <= 25; col++) {
				while ((c = getc(fp)) != EOF)
					if (strchr(".o*#NESW", c) != NULL) break;
				if (c == EOF) { fclose(fp); return 2; }
				grid[row][col] = c;

				if (c == 'o')
					nwhite++;

				char d[] = "NESW";
				if (strchr(d, c) != NULL) {
					init_hy = row;
					init_hx = col;
					init_hd = strchr(d, c) - d;
					grid[row][col] = '.';
				}
			}
		}
		fclose(fp);
		if (init_hd < 0) return 3;

		memset(seen, 0, sizeof(seen));
		seen_id = 1;
		reset();

		return 0;
	}

	void reset() {
		pwhite = 0;
		pgray = 0;
		seen_id++;
		hy = init_hy;
		hx = init_hx;
		hd = init_hd;
		solved = (nwhite == 0);
	}
};

/****************************************************************************/

#define SIZELIM 13

char mem[16*1048576], *memptr=mem;
VVC srl, srlx;

char *cpy(const char *s) {
	char *r = memptr;
	if (r+strlen(s)+16 > mem+sizeof(mem)) {
		fprintf(stderr, "cpy: out of memory\n");
		exit(1);
	}
	do { *memptr++ = *s; } while (*s++ != '\0');
	return r;
}

struct SeqGen {
	char *extra, s[256];
	VVC *out;
	int len;

	void go(int k) {
		s[k] = 0;
		(*out)[k].push_back(cpy(s));

		if (k >= len) return;

		do {
			if (k >= 1 && s[k-1] == 'r') break;
			if (k >= 2 && s[k-2] == 'l' && s[k-1] == 'l') break;
			s[k] = 'l';
			go(k+1);
		} while (0);

		if (k == 0 || s[k-1] == 's') { s[k] = 'r'; go(k+1); }

		s[k] = 's';
		go(k+1);

		for (char *x = extra; *x; x++) {
			s[k] = *x;
			go(k+1);
		}
	}

	void gen(VVC &o, int n, char *x = "") {
		out = &o;
		o.clear();
		o.resize(n+1);
		extra = x;
		len = n;
		go(0);
	}
};

int main(int argc, char *argv[])
{
	Herbert h;
	Scene sc;

	int k = sc.load(argc == 2 ? argv[1] : "lev36");
	if (k != 0) return printf("Failed to load level: %d\n", k);

	SeqGen().gen(srl, 9);
	SeqGen().gen(srlx, 9, "X");

/**
	a(X):<1:srlx>a(<2:srlx>)
	<3:srl>a(<4:srl>)
*/
	int cnt = 0, bestsz = 999;
	char *best = NULL;

	for (int n1 = 1; n1 <= 9; n1++)
	for (int n2 = 1; n2 <= 9; n2++)
	for (int n3 = 0; n3 <= 9; n3++)
	for (int n4 = 0; n4 <= 9; n4++) {
		int sz = 4 + n1 + n2 + n3 + n4;
		if (sz > SIZELIM) continue;
		if (sz >= bestsz) continue;

		foreach(s1, srlx[n1]) {
		  if (strchr(*s1, 'X') == NULL) continue;
		  foreach(s2, srlx[n2])
		  foreach(s3, srl[n3])
		  foreach(s4, srl[n4]) {
			static char src[1024];

			if ((cnt % 500) == 0)
				printf("%d programs tested.\n", cnt);
			cnt++;

			sprintf(src,
				"a(X):%sa(%s)\n"
				"%sa(%s)\n",
				*s1, *s2, *s3, *s4
			);

			if (h.load(src) != 0) continue;

			sc.reset();
			for (int k = 0; k < 1000 && !sc.solved; k++) {
				int c = h.next(500);
				if (c <= 0) break;
				sc.exec(c);
				if (sc.pgray > 5) break;
			}
			if (!sc.solved) continue;

			if (sz < bestsz) {
				bestsz = sz;
				best = cpy(src);
				printf("solution found with size=%d:\n", sz);
				printf("%s\n", best);
			}
		  }
		}
	}

	printf("cnt=%d\n", cnt);
	printf("best size = %d\n", bestsz);
	if (best != NULL) printf("%s\n", best);

	return 0;
}
