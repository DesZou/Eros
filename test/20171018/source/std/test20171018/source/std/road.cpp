#include <stdio.h>
#include <iostream>
#include <cstring>
typedef long long ll;
const int mod=1e9+7;
const int N=500005;
int n,to[N],len[N],vis[N],tim=0,slen[N];
int oncir[N],lev[N],siz[N],head[N],now=0;
int que[N],fr,tl,clen[N],totpair=0,ans=0;
using namespace std;

struct node
{
	int t,next;
}adj[N<<1];
void upd(int& x,int y){x+=y;if (x>=mod) x-=mod;}
void add(int s,int t)
{
	adj[++now]=(node){t,head[s]};
	head[s]=now;
}
void find_circle(int s)
{
	tim++;
	while (!vis[s]) vis[s]=tim,s=to[s];
	if (vis[s]!=tim) return;
	int sum=0;tim++;
	while (vis[s]!=tim) vis[s]=tim,oncir[s]=1,sum++,s=to[s];
	tim++;
	while (vis[s]!=tim) vis[s]=tim,clen[s]=sum,s=to[s];
}
void work(int rt)
{
	que[fr=tl=1]=rt;
	int i,s;
	while (fr<=tl)
	{
		s=que[fr],fr++;
		for (i=head[s];i;i=adj[i].next)
		lev[adj[i].t]=lev[s]+1,que[++tl]=adj[i].t;
	}
	for (s=tl;s>=1;s--)
	{
		siz[que[s]]=1;
		for (i=head[que[s]];i;i=adj[i].next)
		siz[que[s]]+=siz[adj[i].t];
		if (s>1) upd(ans,(ll)len[que[s]]*siz[que[s]]%mod*(lev[que[s]]-1+clen[rt])%mod);
		upd(totpair,lev[que[s]]-1+clen[rt]);
	}
}
void solve(int s)
{
	int tot=0;tl=0;
	while (!vis[s]) vis[s]=1,que[++tl]=s,upd(tot,len[s]),s=to[s];
	int i;
	for (i=1;i<=tl;i++) slen[i]=(slen[i-1]+len[que[i-1]])%mod;
	int pre=0,prez=0,prew=0;
	for (i=1;i<=tl;i++)
	{
		upd(ans,(ll)slen[i]*prez%mod),upd(ans,mod-prew);
		upd(ans,(ll)siz[que[i]]*(tot-slen[i]+mod)%mod*(i-1)%mod);
		upd(ans,(ll)siz[que[i]]*pre%mod);
		upd(pre,slen[i]),upd(prez,siz[que[i]]),upd(prew,(ll)siz[que[i]]*slen[i]%mod);
	}
}
int main()
{
	freopen ("road.in","r",stdin);
	freopen ("road.out","w",stdout);
	scanf ("%d",&n);
	int i;
	for (i=1;i<=n;i++) scanf ("%d %d",&to[i],&len[i]);
	for (i=1;i<=n;i++)
	if (!vis[i]) find_circle(i);
	for (i=1;i<=n;i++)
	if (!oncir[i]) add(to[i],i);
	for (i=1;i<=n;i++)
	if (oncir[i]) work(i);
	memset(vis,0,sizeof(vis));
	for (i=1;i<=n;i++)
	if (oncir[i] && !vis[i]) solve(i);
	totpair=((ll)n*(n-1)%mod-totpair+mod)%mod;
	upd(ans,mod-totpair);
	printf ("%d",ans);
	return 0;
}

