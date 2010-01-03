#include <stdio.h>
#include <math.h>

long nums[40000];

long recur(int i,int j,int N)

{

    long t1=0,t2=0,t=0;

    if(i<0 || j<0 || i>=N || j>=N) return 0;

    if(i==j) t=recur(i+1,j+1,N);

    if(i<=j) t1=(nums[i]>nums[j])+recur(i,j+1,N);

    if(i>=j) t2=(nums[i]>nums[j])+recur(i,j-1,N);

    return t1+t2+t;

}

int main(void)

{

    long int i,j,N,kase=0;

/*    freopen("d.in","r",stdin);*/

    while(1)

    {

        scanf("%d",&N);

        for(i=0;i<N;i++)

            scanf("%ld",&nums[i]);

        if(N==0) break;

        printf("Case %d: %ld\n",++kase,recur(0,0,N));

    }

    return 0;

}
