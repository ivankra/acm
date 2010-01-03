int read(int, char *, int);
int write(int, const char *, int);

int main()
{
	static char tab[256], buf[16384];
	static char a[] = "1234567890-=WERTYUIOP[]\\SDFGHJKL;'XCVBNM,./";
	static char b[] = "`1234567890-QWERTYUIOP[]ASDFGHJKL;ZXCVBNM,.";
	register int i, c;

	for (i = 0; i < 256; i++)
		tab[i] = i;

	for (i = 0; a[i]; i++)
		tab[(unsigned)a[i]] = b[i];

	while ((c = read(0, buf, sizeof(buf))) > 0) {
		for (i = 0; i < c; i++)
			buf[i] = tab[(unsigned)buf[i]];
		write(1, buf, c);
	}

	return 0;
}
