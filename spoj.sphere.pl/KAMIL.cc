main(i,k)
{
	char s[99];
	while(gets(s)) {
		for (i=0, k=1; s[i];)
			k *= strchr("TLDF",s[i++]) ? 2 : 1;
		printf("%d\n", k);
	}
	return 0;
}
