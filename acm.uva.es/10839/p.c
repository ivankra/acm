#include <stdio.h>

int read(int, char *, int);

static const char *data[] = {
	"1", "1", "5", "22", "138", "866", "5834", "40048", "281508",
	"2006698", "14482930", "105527060", "775119252", "5731756720",
	"42628963088", "318621793472", "2391809141820", "18023208400634",
	"136271603094050", "1033449449559724", "7858699316597508",
	"59906766929537116", "457685157228699724", "3503792915352011072",
	"26873014046192639664", "206459748327350872816",
	"1588685066227501860272", "12242566067851779546208",
	"94469949925679476245984", "729895408596195647663168",
	"5645943870845548017753664", "43720821034205638558914304",
	"338911165392799895449278012", "2629674531242561989651362458"
};

static int isdig[256], isdigz[256];

static void mktab()
{
	register int i;

	for (i = 0; i < 256; i++) isdig[i] = 0;
	for (i = '0'; i <= '9'; i++) isdig[i] = 1;

	for (i = 0; i < 256; i++) isdigz[i] = isdig[i];
	isdigz[0] = 1;
}

int main()
{
	static char inbuf[65536];
	static int t;
	register int c, m;
	register char *inp;

	mktab();

	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = '\0';

#define READ(var) { \
	while (!isdigz[*inp]) inp++; \
	if (*inp == '\0') { return 0; } \
	for (var = *inp++ - '0'; isdig[*inp];) \
		var = var * 10 + *inp++ - '0'; \
}

	READ(t);

	for (c = 1; c <= t; c++) {
		READ(m);
		printf("Case %d: %s\n", c, data[(m - 1) / 3]);
	}

	return 0;
}
