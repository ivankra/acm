int read(int, unsigned char *, int);
int write(int, const unsigned char *, int);

int main()
{
	static unsigned char s[] =
		"2`3142536475869708-9=0\\0@~#!$@%#^$&%*^(&)*_(+)|_"
		"w\teqrwteyrutiyoupi[o]pW\tEQRWTEYRUTIYOUPI{O}P"
		"dafsgdhfjgkhlj;k'lDAFSGDHFJGKHLJ:K\"L"
		"czvxbcnvmb,n.m/,CZVXBCNVMB<N>M?<";
	static unsigned char tab[256], buf[16384];
	register int i, n;

	for (i = 0; i < 256; i++)
		tab[i] = i;

	for (i = 0; s[i]; i += 2)
		tab[s[i]] = s[i + 1];

	for (i = 0; i < 256; i++)
		if (tab[i] >= 'A' && tab[i] <= 'Z')
			tab[i] = tab[i] - 'A' + 'a';

	while ((n = read(0, buf, sizeof(buf))) > 0) {
		for (i = 0; i < n; i++)
			buf[i] = tab[buf[i]];
		write(1, buf, n);
	}

	return 0;
}
