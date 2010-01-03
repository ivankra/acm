int read(int, char *, int);
int write(int, char *, int);

int main()
{
        static char s[4096];
	register int i, n;

	while ((n = read(0, s, sizeof(s))) > 0) {
		for (i = 0; i < n; i++)
			if (s[i] != '\n') s[i] -= 7;
		write(1, s, n);
	}

	return 0;
}
