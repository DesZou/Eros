#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n,m,s,k;
int f[N][22],g[N][22],ans;
int last[N],len;
struct Edge{int to,next,val;Edge(int to=0,int next=0,int val=0):to(to),next(next),val(val){}}e[N<<1];
void add_edge(int u,int v,int w){e[++len]=Edge(v,last[u],v);last[u]=len;}
inline int get(int x){return x?(x-1)/s+1:0;}
void dfs(int x,int fa)
{
	for(int i=last[x];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==fa)continue;
		dfs(v,x);
		for(int j=1;j<=k;j++)
		{
			f[x][j]=min(n,f[x][j]+f[v][j-1]);
			g[x][j]+=g[v][j-1];
		}
	}
    int tmp;g[x][0]++;
    if (g[x][k])
    {
        tmp=get(g[x][k]);
        f[x][0]=min(1ll*n,1ll*tmp*s);
        ans+=tmp;
    }
    for(int i=0;i<=k;i++)
    {
        int j=k-i;
        int tmp=min(f[x][i],g[x][j]);
        f[x][i]-=tmp,g[x][j]-=tmp;
    }
    for(int i=0;i<k;i++)
    {
        int j=k-1-i;
        int tmp=min(f[x][i],g[x][j]);
        f[x][i]-=tmp,g[x][j]-=tmp;
    }	
}
inline void solve()
{
    for(int i=0;i<=k;i++)
    {
        for(int j=k;j>=0;j--)
        if(i+j<=k)
        {
            int tmp=min(f[1][j],g[1][j]);
            f[1][i]-=tmp;
            g[1][j]-=tmp;
        }
    }
    int tot=0;
    for(int i=0;i<=k;i++)tot+=g[1][i];
    ans+=get(tot);
    printf("%d\n",ans);
}
inline void init()
{
	freopen("repulsed.in","r",stdin);
    freopen("repulsed.out","w",stdout);
    scanf("%d%d%d",&n,&s,&k);
    for(int x,y,i=1;i<n;i++)
    {
        scanf("%d%d",&x,&y);
        add_edge(x,y,1);add_edge(y,x,1);
    }
}
int main()
{
	init();
    dfs(1,0);
    solve();
    return 0;
}
