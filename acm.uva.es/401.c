#include <stdio.h>
#include <string.h>

char V[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
char R[] = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";

int main()
{
	char rev[256], buf[65536], str[65536], fmir, fpal;
	int i, j, n;

	memset(rev, 0, sizeof(rev));

	for (i = 0; R[i]; i++)
		rev[V[i]] = ((R[i] == ' ') ? 0 : R[i]);

	while (fgets(buf, sizeof(buf), stdin)) {
		for (i = 0, n = 0; buf[i] && buf[i] != '\n' && buf[i] != '\r'; i++)
			if (('A'<=buf[i]&&buf[i]<='Z') || ('1'<=buf[i]&&buf[i]<='9'))
				str[n++] = buf[i];
			else if (buf[i] == '0')
				str[n++] = 'O';
			else if (buf[i] >= 'a' && buf[i] <= 'z')
				str[n++] = buf[i] - 'a' + 'A';
		str[n] = '\0';

		while (i > 0 && buf[i-1] == ' ') i--;
		buf[i] = '\0';

		for (i = 0, j = n - 1; i < n && str[i]==str[j]; i++, j--);
		fpal = (i >= n);

		for (i = 0, j = n-1; i < n; i++, j--)
			if (rev[str[i]]==0 || rev[str[j]]==0 || str[i]!=rev[str[j]]) break;
		fmir = (i >= n);

		if (fpal && fmir)
			printf("%s -- is a mirrored palindrome.\n\n", buf);
		else if (!fpal && fmir)
			printf("%s -- is a mirrored string.\n\n", buf);
		else if (fpal)
			printf("%s -- is a regular palindrome.\n\n", buf);
		else
			printf("%s -- is not a palindrome.\n\n", buf);
	}

	return 0;
}
