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
const int maxn=5e5+10,mod=1e9+7;
typedef int INT[maxn];
struct edge
{
	int to,next;
	edge(){}
	edge(int to,int next):to(to),next(next){}
}e[maxn];
int n,tot=0,dfsClock=0,sccCnt=0,top=0;
bool ins[maxn]={0};
INT pre,low,dfn,sccno,stack,num,sum,V;
int read();
void add(int,int);
void findScc();
void dfs(int);
int main()
{
	fr(road);
	n=read();
	mem(pre,-1);
	for(int i=1,t,v;i<=n;i++)
	{
		t=read(),v=read();
		add(i,t),V[i]=v;
	}
	findScc();
	mem(num,0),mem(sum,0);
	for(int i=1;i<=n;i++)
	{
		num[sccno[i]]++;
		sum[sccno[i]]=(1ll*sum[sccno[i]]+1ll*V[i])%mod;
	}
	ll ans=0;
	for(int i=1;i<=sccCnt;i++)
	{
		ll x=1ll*num[i]*(num[i]-1)/2;
		ans=(ans+1ll*sum[i]*x)%mod;
		ans=(ans+mod-(1ll*num[i]*(n-num[i])))%mod;
	}
	printf("%lld\n",ans);
//	fprintf(stderr,"%.3f s\n",clock()*1.0/CLOCKS_PER_SEC);
	return 0;
}
void findScc()
{
	dfsClock=sccCnt=0;
	mem(low,0),mem(ins,0),mem(dfn,0),mem(stack,0),mem(sccno,0);
	for(int i=1;i<=n;i++) if(!dfn[i]) dfs(i);
}
void dfs(int s)
{
	dfn[s]=low[s]=++dfsClock;
	ins[stack[++top]=s]=true;
	for(int i=pre[s];~i;i=e[i].next)
	{
		int ito=e[i].to;
		if(!dfn[ito]) dfs(ito),low[s]=min(low[s],low[ito]);
		else if(ins[ito]) low[s]=min(low[s],dfn[ito]);
	}
	if(low[s]==dfn[s])
	{
		sccCnt++;
		while(true)
		{
			int x=stack[top--];
			ins[x]=false;
			sccno[x]=sccCnt;
			if(x==s) break;
		}
	}
}
void add(int from,int to)
{
	e[++tot]=edge(to,pre[from]);pre[from]=tot;
}
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-'0',c=getchar();
	return x*f;
}
/*
4
2 1
3 2
1 3
4 3
*/
