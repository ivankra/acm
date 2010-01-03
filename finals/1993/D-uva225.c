#include <stdio.h>

char *sol7[] = {
	"enwnwse", "eswswne", "neseswn", "nwswsen", "senenws", "swnwnes",
	"wnenesw", "wsesenw", NULL
};

char *sol8[] = {
	"enwswsen", "eswnwnes", "neswswne", "nwsesenw", "senwnwse", "swnenesw",
	"wneseswn", "wsenenws", NULL
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

char *sol_none[] = { NULL };

int n, m, ox[64], oy[64];
int dx[256], dy[256];

int in(int a, int x, int b)
{
	return (a <= x && x <= b) || (b <= x && x <= a);
}

int check(char *s)
{
	int x0, y0, x1, y1, k, i;

	for (x0 = y0 = k = 0; k < n; k++, x0 = x1, y0 = y1) {
		x1 = x0 + (k + 1) * dx[s[k]];
		y1 = y0 + (k + 1) * dy[s[k]];

		for (i = 0; i < m; i++)
			if (in(x0, ox[i], x1) && in(y0, oy[i], y1)) return 0;
	}

	return 1;
}

int main()
{
	int i, r, t;
	char **s;

	dx['n'] = dx['s'] = 0; dx['w'] = -1; dx['e'] = 1;
	dy['w'] = dy['e'] = 0; dy['s'] = -1; dy['n'] = 1;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &m) == 2;) {
		if (n == 7)
			s = sol7;
		else if (n == 8)
			s = sol8;
		else if (n == 15)
			s = sol15;
		else if (n == 16)
			s = sol16;
		else
			s = sol_none;

		for (i = 0; i < m; i++)
			scanf("%d %d", &ox[i], &oy[i]);

		for (r = 0, i = 0; s[i] != NULL; i++)
			if (check(s[i])) {
				printf("%s\n", s[i]);
				r++;
			}

		printf("Found %d golygon(s).\n\n", r);
	}

	return 0;
}
