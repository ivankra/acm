#include <ext/rope>
using namespace std;
char s[9999];int T,N,i,o[999];string w[1<<17];
int C(string a,string b){
	for(i=0;i<a.size()&&i<b.size();i++)
		if(o[a[i]]-o[b[i]])return o[a[i]]<o[b[i]];
	return a.size()<b.size();
}
int main(){
	for(scanf("%d",&T);scanf("%s%d ",s,&N),T--;){
		for(i=0;s[i];i++)o[s[i]]=i;
		for(i=N;i--;)gets(s),w[i]=s;
		sort(w,w+N,C);
		for(i=0;i<N;)puts(w[i++].c_str());puts("");
	}
}
