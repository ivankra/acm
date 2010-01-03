#include <stdio.h>
#include <string.h>

void zrot(char s[])
{
	int a = s[1];
	s[1] = s[3];
	s[3] = s[4];
	s[4] = s[2];
	s[2] = a;
}

void xrot(char s[])
{
	int a = s[0];
	s[0] = s[1];
	s[1] = s[5];
	s[5] = s[4];
	s[4] = a;
}

void yrot(char s[])
{
	int a = s[0];
	s[0] = s[3];
	s[3] = s[5];
	s[5] = s[2];
	s[2] = a;
}

int main()
{
	static char s[1024];
	int i, j, k;

	while (scanf(" %[A-Za-z0-9]", s) == 1) {
		for (i = 0; i < 4; i++, xrot(s))
			for (j = 0; j < 4; j++, yrot(s))
				for (k = 0; k < 4; k++, zrot(s))
					if (memcmp(s, s + 6, 6) == 0) goto ok;

		printf("FALSE\n");
		continue;

ok:		printf("TRUE\n");
	}

	return 0;
}
