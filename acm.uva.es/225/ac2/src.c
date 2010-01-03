#include <string.h>
#include <stdlib.h>

int read(int, char *, int);
int write(int, char *, int);

char *sol7[] = {
	"enwnwse", "eswswne", "neseswn", "nwswsen", "senenws", "swnwnes",
	"wnenesw", "wsesenw", NULL
};

int pre7[] = {
	0, 1, 0, 1, 0, 1, 0, 1
};

char *sol8[] = {
	"enwswsen", "eswnwnes", "neswswne", "nwsesenw", "senwnwse", "swnenesw",
	"wneseswn", "wsenenws", NULL
};

int pre8[] = {
	0, 1, 0, 1, 0, 1, 0, 1
};

char *sol15[] = {
	"enenwswnwswsene", "enenwswswnwnese", "eneswnwnwswnese",
	"eneswswswswnene", "enwneswnwseswne", "enwseswswsenwne",
	"enwswnenwsenesw", "enwswseseswnwne", "enwswseswsenenw",
	"esenwnwnwnwsese", "esenwswswnwsene", "eseswnwnwswsene",
	"eseswnwswnwnese", "eswnenwnwneswse", "eswnwnenenwswse",
	"eswnwnenwnesesw", "eswnwseswnesenw", "eswsenwswnenwse",
	"neneswseswswnen", "neneswswsesenwn", "nenwseseswsenwn",
	"nenwswswswsenen", "nesenwseswnwsen", "neswnwswswnesen",
	"neswseneswnenws", "neswswnwnwsesen", "neswswnwswnenes",
	"nwneseseseswnwn", "nwneswswseswnen", "nwnwseseswswnen",
	"nwnwseswsesenwn", "nwsenesesenwswn", "nwseseneneswswn",
	"nwsesenesenwnws", "nwseswnwsenwnes", "nwswneswseneswn",
	"seneswnenwswnes", "senwnesenwseswn", "senwnwswnwsesen",
	"senwnwswswnenes", "senwswnwnwsenes", "sesenwnenwnwses",
	"sesenwnwnenesws", "seswnenenwnesws", "seswnwnwnwneses",
	"swneneseneswswn", "swnenesesenwnws", "swnenwswneswsen",
	"swneseneneswnws", "swnwsenwnesenws", "swsenenenenwsws",
	"swsenwnwnenwses", "swswnenenwnwses", "swswnenwnenesws",
	"wnenwseneswsenw", "wnesenwneswnwse", "wneseswseswnwne",
	"wneseswswsenenw", "wneswseseswnenw", "wnwneseneseswnw",
	"wnwnesesenenwsw", "wnwsenenesenwsw", "wnwsesesesenwnw",
	"wsenenwnenwswse", "wsenenwnwnesesw", "wseneswsenwswne",
	"wsenwnenenwsesw", "wseswnesenwnesw", "wswneneneneswsw",
	"wswneseseneswnw", "wswseneneseswnw", "wswsenesenenwsw",
	NULL
};

int pre15[] = {
	0, 7, 3, 5, 2, 3, 4, 5, 8, 1, 5, 3, 7, 2, 4, 8, 5, 3, 0, 7, 3, 5, 2, 3,
	4, 5, 8, 1, 5, 3, 7, 2, 4, 8, 5, 3, 0, 3, 5, 8, 4, 2, 7, 3, 5, 1, 8, 5,
	4, 3, 2, 5, 3, 7, 0, 3, 5, 8, 4, 2, 7, 3, 5, 1, 8, 5, 4, 3, 2, 5, 3, 7
};

char *sol16[] = {
	"enenwnwnwswsesen", "enenwnwswnwsenes", "enenwswnwnwneses",
	"enenwswswswsenen", "eneswnwswswnesen", "eneswswnwnwsesen",
	"eneswswnwswnenes", "enwnenwnwseswsen", "enwneswnwnenwses",
	"enwneswswseswnen", "enwnwneneswswsen", "enwnwnenwseseswn",
	"enwnwneswnesenws", "enwswneswseneswn", "esenwnwswnwsesen",
	"esenwnwswswnenes", "esenwswnwnwsenes", "eseswnwnwnwneses",
	"eseswnwswswsenen", "eseswswnwswnesen", "eseswswswnwnenes",
	"eswnwsenwnesenws", "eswsenwnwnenwses", "eswsenwswseswnen",
	"eswseswswnenwnes", "eswswsenwseneswn", "eswswsesenwnwnes",
	"eswswseswnenenws", "neneseseswswnwne", "neneseswseswnenw",
	"neneswsesesenwnw", "neneswswswswnene", "nenwseswswsenwne",
	"nenwswseseswnwne", "nenwswseswsenenw", "neseneseswnwswne",
	"nesenwseseneswnw", "nesenwswswnwsene", "nesesenenwswswne",
	"neseseneswnwnwse", "nesesenwsenwnesw", "neswsenwswnenwse",
	"nwneseswseswnwne", "nwneseswswsenenw", "nwneswseseswnenw",
	"nwnwsesesesenwnw", "nwnwseswswswnene", "nwnwswseswsenwne",
	"nwnwswswsesenenw", "nwseswnesenwnesw", "nwswneseseneswnw",
	"nwswneswswnwsene", "nwswnwswsenesenw", "nwswswneswnenwse",
	"nwswswnwnesesenw", "nwswswnwsenenesw", "senenesenwswswne",
	"seneneseswnwnwse", "seneneswneswsenw", "senesenenwswnwse",
	"seneswnenesenwsw", "seneswnwnwswnese", "senwneswnwseswne",
	"sesenenenwnwswse", "sesenenwnenwsesw", "sesenwneneneswsw",
	"sesenwnwnwnwsese", "seswnenwnwneswse", "seswnwnenenwswse",
	"seswnwnenwnesesw", "swnenwseneswsenw", "swnwnwsenwseswne",
	"swnwnwswnesesenw", "swnwnwswsenenesw", "swnwsenenesenwsw",
	"swnwsenwnwswnese", "swnwswnwnesenesw", "swsenenwnenwswse",
	"swsenenwnwnesesw", "swsenwnenenwsesw", "swswneneneneswsw",
	"swswnenwnwnwsese", "swswnwnenwneswse", "swswnwnwnenesesw",
	"wnenenwneswswsen", "wnenenwnwseseswn", "wnenenwsenwswnes",
	"wnenwneneswseswn", "wnenwsenenwnesws", "wnenwseseswsenwn",
	"wnesenwseswnwsen", "wnwneneneseswswn", "wnwneneseneswnws",
	"wnwnesenenenwsws", "wnwneseseseswnwn", "wnwsenesesenwswn",
	"wnwseseneneswswn", "wnwsesenesenwnws", "wseneswnenwswnes",
	"wseseswneswnwsen", "wseseswsenwnwnes", "wseseswswnenenws",
	"wseswnenenwnesws", "wseswneseswsenwn", "wseswsesenwnenws",
	"wswneneseneswswn", "wswnenesesenwnws", "wswneseneneswnws",
	"wswsenenenenwsws", "wswseneseseswnwn", "wswsesenesenwswn",
	"wswsesesenenwnws", NULL
};

int pre16[] = {
	0, 7, 5, 7, 3, 5, 9, 2, 5, 7, 4, 8, 7, 3, 1, 9, 5, 3, 7, 5, 7, 2, 3, 7,
	5, 4, 7, 8, 0, 7, 5, 7, 3, 5, 9, 2, 5, 7, 4, 8, 7, 3, 1, 9, 5, 3, 7, 5,
	7, 2, 3, 7, 5, 4, 7, 8, 0, 8, 7, 4, 5, 7, 3, 2, 7, 5, 7, 3, 5, 9, 1, 3,
	7, 8, 4, 7, 5, 2, 9, 5, 3, 7, 5, 7, 0, 8, 7, 4, 5, 7, 3, 2, 7, 5, 7, 3,
	5, 9, 1, 3, 7, 8, 4, 7, 5, 2, 9, 5, 3, 7, 5, 7
};

char *sol_none[] = { NULL };
int pre_none[] = { 0 };

char **sol_list[] = {
	sol_none, sol_none, sol_none, sol_none, sol_none, sol_none, sol_none,
	sol7, sol8, sol_none, sol_none, sol_none, sol_none, sol_none, sol_none,
	sol15, sol16, sol_none, sol_none, sol_none, sol_none
};

int *pre_list[] = {
	pre_none, pre_none, pre_none, pre_none, pre_none, pre_none, pre_none,
	pre7, pre8, pre_none, pre_none, pre_none, pre_none, pre_none, pre_none,
	pre15, pre16, pre_none, pre_none, pre_none, pre_none
};

int n, m, ox[64], oy[64];
int dx[256], dy[256], xm[256], ym[256];

static inline int in(int a, int x, int b)
{
	return (a <= x && x <= b) || (b <= x && x <= a);
}

static int check(char *s, int k)
{
	int x0, y0, x1, y1, i;

	x0 = xm[k];
	y0 = ym[k];

	for (; k <= n; k++, s++, x0 = x1, y0 = y1) {
		xm[k] = x0;
		ym[k] = y0;

		x1 = x0 + k * dx[*s];
		y1 = y0 + k * dy[*s];

		if (x0 == x1) {
			for (i = 0; i < m; i++)
				if (ox[i] == x0 && in(y0, oy[i], y1))
					return (k - 1);
		} else {
			for (i = 0; i < m; i++)
				if (oy[i] == y0 && in(x0, ox[i], x1))
					return (k - 1);
		}
	}

	return n;
}

int main()
{
	static char inbuf[1048576], outbuf[4*1048576], tmp[256];
	static int isdig[256], isdigm[256];
	char *p, *q, *u, **s;
	int i, j, r, cl, t, *pre;

	dx['n'] = dx['s'] = 0; dx['w'] = -1; dx['e'] = 1;
	dy['w'] = dy['e'] = 0; dy['s'] = -1; dy['n'] = 1;
	xm[1] = ym[1] = 0;

	for (i = '0'; i <= '9'; i++) isdig[i] = 1;
	for (i = '0'; i <= '9'; i++) isdigm[i] = 1; isdigm['-'] = 1;

#define RU(x) {while(!isdig[*p])p++;for(x=*p++-'0';isdig[*p];)x=x*10+*p++-'0';}
#define RS(x) {while(!isdigm[*p])p++;if(*p=='-'){p++;for(x=*p++-'0';isdig[*p];)\
	       x=x*10+*p++-'0';x=-x;}else{for(x=*p++-'0';isdig[*p];)x=x*10+*p++-'0';}}
#define W(x) {if(x==0){*q++='0';}else{for(u=tmp;x>0;x/=10)*u++=(x%10)+'0';while(u-->tmp)*q++=*u;}}
#define P(c) {*q++=(c);}

	read(0, p = inbuf, sizeof(inbuf));
	q = outbuf;

	RU(t);
	while (t-- > 0) {
		RU(r); n=r;
		RU(r); m=r;

		for (i = 0; i < m; i++) {
			RS(r); ox[i]=r;
			RS(r); oy[i]=r;
		}

		s = sol_list[n];
		pre = pre_list[n];

		for (r = 0, cl = 1, i = 0; s[i] != NULL; i++) {
			j = (pre[i] < cl) ? pre[i] : cl;
			if (j == cl && s[i - 1][j] == s[i][j]) continue;

			cl = check(s[i] + j, j + 1);
			if (cl == n) {
				for (u = s[i]; *u;) *q++ = *u++;
				*q++ = '\n';
				r++;
			}
		}

		P('F');P('o');P('u');P('n');P('d');P(' ');W(r);P(' ');
		P('g');P('o');P('l');P('y');P('g');P('o');P('n');P('(');P('s');P(')');
		P('.');P('\n');P('\n');
	}

	write(1, outbuf, q - outbuf);
	exit(0);
	return 0;
}
