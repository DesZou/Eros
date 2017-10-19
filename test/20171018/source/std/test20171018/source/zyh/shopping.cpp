#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#define mem(a,b) memset(a,b,sizeof(a))
#define fr(x) freopen(#x ".in","r",stdin);freopen(#x ".out","w",stdout)
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
using namespace std;
typedef long long ll;
const int maxn=1e5+10;
int n,m,w[maxn],p[maxn];
int read();
ll solve(int);
int main()
{
	fr(shopping);
	n=read(),m=read();
	for(int i=1;i<=n;i++) w[i]=read(),p[i]=read();
	while(m--)
	{
		int op,x,W,P;
		op=read(),x=read();
		if(op==1) W=read(),P=read(),w[x]=W,p[x]=P;
		else printf("%lld\n",solve(x));
	}
//	fprintf(stderr,"%.3f s\n",clock()*1.0/CLOCKS_PER_SEC);
	return 0;
}
ll solve(int k)
{
	ll ret=0;
	while(true)
	{
		int ans=-1,id=-1;
		for(int i=1;i<=n;i++)
		{
			if(w[i]>ans&&p[i]<=k) ans=w[i],id=i;
			else if(w[i]==ans&&p[i]<p[id]) id=i;
		}
		if(id==-1) return ret;
		k-=p[id];ret+=ans;
	}
}
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-'0',c=getchar();
	return x*f;
}