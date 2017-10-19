#include<bits/stdc++.h>
using namespace std;
const int N=5e2+10;
const int inf=1e9+10;
typedef long long ll;
ll n,m,len,last[N],P[N];
ll inq[N],ans[N][N];
struct Distance {ll Pmx,Emx,val;}dis[N];
struct Edge{int to,next;ll val;Edge(int to=0,int next=0,ll val=0):to(to),next(next),val(val){}}e[N*N];
void add_edge(int u,int v,ll w){e[++len]=Edge(v,last[u],w);last[u]=len;}
void SPFA(int s)
{
	for(int i=1;i<=n;i++)
	{
		inq[i]=0;
		dis[i].val=inf;
		dis[i].Pmx=P[i];dis[i].Emx=0;
	}
	queue<int>q;
	dis[s].val=0;
	q.push(s);inq[s]=1;
	while(!q.empty())
	{
		int cur=q.front();
		q.pop();inq[cur]=0;
		for(int i=last[cur];i;i=e[i].next)
		{
			int id=e[i].to;
			int nowval=max(dis[cur].Pmx,P[id])*max(dis[cur].Emx,e[i].val);
			if(nowval<dis[id].val)
			{
				dis[id].val=nowval;
				dis[id].Pmx=max(dis[cur].Pmx,P[id]);
				dis[id].Emx=max(dis[cur].Emx,e[i].val);
				if(!inq[id])
				{
					q.push(id);
					inq[id]=1;
				}
			}
		}
	}
	for(int i=1;i<=n;i++) ans[s][i]= dis[i].val>inf?-1:dis[i].val;
}
int main()
{
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&P[i]);
	for(int u,v,w,i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		add_edge(u,v,w);add_edge(v,u,w);
	}
	for(int i=1;i<=n;i++)SPFA(i);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			printf("%lld ",ans[i][j]);
		puts("");
	}
	return 0;
}
