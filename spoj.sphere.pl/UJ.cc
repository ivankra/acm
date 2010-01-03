#include <cstdio>
int main(){
	long long z[999],c,r=1e15;
	int a,b,n,i;
	while(scanf("%d %d",&a, &b),a) {
		for(z[0]=n=1;b--;){
			for(c=i=0;i<n;i++,c/=r)
				z[i]=(c+=z[i]*a)%r;
			if(c)z[n++]=c;
		}
		for(i=n;i--;)printf(i+1-n?"%.15lld":"%lld",z[i]);
		printf("\n");
	}
}
