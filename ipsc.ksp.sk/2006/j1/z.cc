#include <cstdio>
#include <cstring>

char F[1024][20];
char G[1024][20];

int main() {
	FILE *f = fopen("tab", "r");
	FILE *g = fopen("tab.j1", "r");
	char s1[1024], s2[1024];

	for (int n = 1; fgets(s1, sizeof(s1), f) != NULL &&
	                fgets(s2, sizeof(s2), g) != NULL; n++) {
		while (strlen(s1) > 0 && s1[strlen(s1)-1] == '\n') s1[strlen(s1)-1] = 0;
		while (strlen(s2) > 0 && s2[strlen(s2)-1] == '\n') s2[strlen(s2)-1] = 0;
		strcpy(F[n], s1);
		strcpy(G[n], s2);
	}

	for (int a = 1; a <= 334; a++)
	for (int b = 1; b <= 334; b++) {
		sprintf(s1, "%s%s", F[a], F[b]);
		sprintf(s2, "%s%s", G[a], G[b]);
		if (strcmp(s1,s2)==0) printf("%d %d\n",a,b);

	}

} 
