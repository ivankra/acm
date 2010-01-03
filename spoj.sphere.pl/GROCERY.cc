#include <cstdio>
int main(){
 int m=2000000000;
 long long p,q;
 for(int a=1;a<=125;a++)
 for(int b=a;a*b*b*b<=m;b++)
 for(int c=b;a*b*c*c<=m;c++){
  p=1000000LL*(a+b+c);
  q=a*b*c-1000000;
  if(q>0&&p>=c*q&&p%q==0){
   p/=q;
   if(a*b*c*p<=m){
    #define P(x,c)printf("%d.%.2d%c",int(x)/100,int(x)%100,c);
    P(a,' ')P(b,' ')P(c,' ')P(p,'\n')
   }
  }
 }
}
