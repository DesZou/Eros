#include<iostream>
#include<cstdio>
using namespace std;
int mod=1e9+7;
int getint()
{
	int ans=0;char ch;
	do{ch=getchar();}while(ch<'0'||ch>'9');
	ans=ch-'0';
	while(isdigit(ch=getchar()))ans=ans*10+ch-'0';
	return ans;
}
struct T
{
	int to,nxt,v;
}sid[500001];
long long siz[500001],tim[500001];
int fi[500001];
void add(int x,int y)
{
	sid[y].to=y;sid[y].nxt=fi[x];fi[x]=y;sid[y].v=getint();
}
bool vis[500001],cel[500001],on[500001];
int str[500001],cnt=0;
bool fnd(int dis,int x)
{
	if(cel[dis])
	  return false;
	cel[dis]=true;
	for(int i=fi[dis];i;i=sid[i].nxt)
	{
		if(sid[i].to==x||fnd(sid[i].to,x))
		{
			str[++cnt]=dis;
			on[dis]=true;
			return true;
		}
	}
	return false; 
}
long long used=0,ans=0,mid;
void dfs(int dis)
{
	siz[dis]=cnt;
	for(int i=fi[dis];i;i=sid[i].nxt)
	{
		if(on[sid[i].to])
		  continue;
		dfs(sid[i].to);
		siz[dis]+=siz[sid[i].to];
	}
	tim[dis]=siz[dis];
	mid+=siz[dis];
}
int main()
{
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	int n;
	n=getint();
	for(int i=1;i<=n;i++)
	  add(getint(),i);
	for(int i=1;i<=n;i++)
	{
		if(vis[i]||cel[i])
		  continue;
		if(!fnd(i,i))
		  continue;
		long long ant=0,xxx=0;
		for(int j=1;j<=cnt;j++)
		  dfs(str[j]);
		for(int j=1;j<=cnt;j++)
		  ant+=siz[str[j]];
		for(int j=1;j<=cnt;j++)
		  mid=mid-siz[str[j]]+ant; 
		if(cnt==1)
		{
			tim[str[1]]=0;
			continue;
		}
		for(int j=1;j<=cnt;j++)
		  tim[str[j]]=(cnt-2)*(ant-siz[str[j]]-siz[sid[str[j]].to])+siz[str[j]]*(cnt-1);
		cnt=0;
	}
	used=n*n-mid;
	for(int i=1;i<=n;i++)
	  ans=(ans+sid[i].v*tim[i])%mod;
	ans=(ans+mod-used)%mod;
	cout<<ans;
}
/*
4
2 1
3 1
1 1
3 1

4
2 1
3 2
1 3
4 3
*/
