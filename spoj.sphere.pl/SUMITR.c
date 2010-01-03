#define R(x)scanf("%d",&x)
int a[99];main(T,n,r,i,j){for(R(T);T--;){R(n);for(a[r=0]=0;++r<=n;){for(a[i=r]=0;--i;)if(a[i-1]>a[i])a[i]=a[i-1];for(i=0;i<r;i++){R(j);a[i]+=j;}}for(i=j=0;i<n;i++)if(a[i]>j)j=a[i];printf("%d\n",j);}}
