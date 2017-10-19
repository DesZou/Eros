#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<queue>
#define nn 500011
using namespace std;
typedef long long lo;
const lo mod=1000000007;
int fir[nn],sta[nn],t[nn],num[nn],fi[nn],top[nn],nxt[nn<<1],to[nn<<1],w[nn<<1],e,n,st,tim;
lo di[nn];
bool vis[nn];
lo res;
int read()
{
	int ans=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) {ans=ans*10+ch-'0';ch=getchar();}
	return ans*f;
}
void add(int u,int v,int len)
{
	nxt[++e]=fir[u];fir[u]=e;to[e]=v;w[e]=len;
}
void tarjan(int x)
{
	t[x]=top[x]=++tim;sta[++st]=x;vis[x]=1;
	for(int i=fir[x];i;i=nxt[i])
	  if(!t[to[i]])
	  {
	  	tarjan(to[i]);
	  	top[x]=min(top[x],top[to[i]]);
	  	if(top[to[i]]==t[to[i]])
	  	{
	  		num[x]=num[to[i]]+1;
	  		di[x]=(di[to[i]]+(lo)num[x]*w[i]%mod)%mod;
	  		return;
	  	}
	  }
	  else if(vis[to[i]])
	    top[x]=min(top[x],t[to[i]]);
	if(top[x]==t[x])
	{
		lo sum=0,size=0;
		do
		{
			sum=(sum+w[fir[sta[st]]])%mod;
			size++;
			vis[sta[st]]=0;
			st--;
		}while(sta[st+1]!=x);
		if(size==1) return;
		int cnt=size-1,o;
		o=x;       ////
		do
		{
			di[x]=(di[x]+(lo)cnt*w[fir[o]]%mod)%mod;
			cnt--;
			o=to[fir[o]];
		}while(o&&o!=x);         ////
		num[x]=size-1;
		o=fi[x];
		while(o&&o!=x)
		{
			di[o]=(di[to[fir[o]]]+(lo)w[fir[o]]*size%mod-sum)%mod;
			num[o]=size-1;
			o=fi[o];
		}
	}
}
int main()
{
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	int v,len;
	n=read();
	for(int i=1;i<=n;i++)
	  v=read(),len=read(),add(i,v,len),fi[v]=i;
	for(int i=1;i<=n;i++)
	  if(!t[i])
	    tarjan(i);
	for(int i=1;i<=n;i++)
	  res=(res+di[i]-n+1+num[i]+mod)%mod;
	printf("%lld",res);
	return 0;
}
/*
4
2 1
3 2
1 3
4 3
*/
