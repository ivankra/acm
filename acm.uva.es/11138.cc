#include <stdio.h>
#include <cstring>
 
#define MAX_BOLTS 500
#define MAX_NUTS  500
 
/* global copy of the input data */
int nuts,bolts;
int fits[MAX_BOLTS][MAX_NUTS];

void read_input_data()
{
   int n,b;
   
   scanf("%d%d",&bolts,&nuts);
   for(b=0;b<bolts;b++){
      for(n=0;n<nuts;n++){
         scanf("%d",&fits[b][n]);
      }
   }
}


int match[512], seen[512];
int res;

int aug(int b) {
	if (seen[b]++) return 0;

	for (int i = 0; i < nuts; i++) {
		if (fits[b][i] && (match[i] < 0 || aug(match[i]))) {
			match[i] = b;
			return 1;
		}
	}

	return 0;
}

void init_match()
{
	memset(match, 0xff, sizeof(match));

	res = 0;
	for (int i = 0; i < bolts; i++) {
		memset(seen, 0, sizeof(seen));
		if (aug(i)) res++;
	}
}
   
  
int main()
{
   int cases,caseno;
   
   scanf("%d",&cases);
   for(caseno=1;caseno<=cases;caseno++){
      read_input_data();
      init_match();
      printf("Case %d: ",caseno);
      printf("a maximum of %d nuts and bolts ", res);
      printf("can be fitted together\n");
   }
      
}
