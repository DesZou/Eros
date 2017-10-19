//Twenty
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<queue>
using namespace std;
typedef long long LL;
const int maxn=500005;
const int mod=1e9+7;
int n;

void read(int &x) {
    int ret=0,f=1; char ch=getchar();
    while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
    if(ch=='-') f=-1,ch=getchar();
    for(;ch>='0'&&ch<='9';ch=getchar()) ret=ret*10+ch-'0';
    x=ret;
}

int ecnt,fir[maxn],nxt[maxn*2],to[maxn*2],val[maxn*2];
void add(int u,int v,int w) {
    nxt[++ecnt]=fir[u]; fir[u]=ecnt; to[ecnt]=v; val[ecnt]=w;
    nxt[++ecnt]=fir[v]; fir[v]=ecnt; to[ecnt]=u; val[ecnt]=w;
}

void init() {
    read(n);
    for(int i=1;i<=n;i++) {
	    int u,v,w;
	    u=i; read(v); read(w);
	    add(u,v,w);
	}
}

int xx,yy,R[maxn],sz[maxn],f[maxn][20],g[maxn][20];
LL ans,ww;
void dfs(int x,int fa) {
    R[x]=R[fa]+1; 
    f[x][0]=fa;
    sz[x]=1;
    for(int i=fir[x];i;i=nxt[i]) if(to[i]!=fa){
    	if(R[to[i]]) {
		    xx=x,yy=to[i],ww=val[i];
		    continue;
	    }
	    g[to[i]][0]=val[i];
	    dfs(to[i],x);
	    sz[x]+=sz[to[i]];
	}
}

void dfs2(int x,int fa) {
    for(int i=fir[x];i;i=nxt[i]) if(to[i]!=fa){
	    if(x==xx&&to[i]==yy) continue;
	    (ans+=(((LL)val[i]*sz[to[i]])%mod*(sz[1]-sz[to[i]])%mod))%=mod;
		dfs2(to[i],x);
	}
}

int ms[maxn][20],ls[maxn][20],lca;
LL get_lca(int x,int y) {
	LL res=0;
	int tp=0;
    if(R[x]!=R[y]) {
	    if(R[x]<R[y]) swap(x,y);
	    while(R[x]<R[y]) {
		    (res+=g[x][0])%=mod;
		    x=f[x][0];
		    ms[x][0]=sz[x]-tp;
		    ls[f[x][0]][0]=ms[f[x][0]][0]*g[x][0]%mod;
		    tp=sz[x];
		}
	}
		
	while(x!=y) {
	    (res+=g[x][0])%=mod;
	    (res+=g[y][0])%=mod;
	    ms[x][0]=sz[x]-tp;
	    ls[f[x][0]][0]=ms[f[x][0]][0]*g[x][0]%mod;
		tp=sz[x];
	    x=f[x][0]; y=f[y][0];
	}
	lca=x;
	return res;
}

void make_st() {
	for(int i=1;i<=19;i++) {
		for(int j=1;j<=maxn;j++) {
		    f[j][i]=f[f[j][i-1]][i-1];
	        g[j][i]=g[j][i-1]+g[f[j][i-1]][i-1];
	        ms[j][i]=ms[j][i-1]+ms[f[j][i-1]][i-1];
	        ls[j][i]=ls[j][i-1]+ls[f[j][i-1]][i-1];
        }
	}
}

LL tp,tpp;
void work() {
    dfs(1,0);
    dfs2(1,0);
    tp=get_lca(xx,yy);
    make_st();
    tpp=tp/2;
    if(R[xx]<R[yy]) swap(xx,yy);
    LL now=ww,tpj,tpsz,tpx,ans2=0;
    while(now<tp) {
    	tpj=0; tpsz=0; tpx=xx;
	    for(int i=19;i>=0;i--) {
		    if(f[tpx][i]&&R[f[tpx][i]]<=R[lca]&&g[tpx][i]+now<tp) {
			    tpj+=ls[tpx][i];
			    tpsz+=ms[tpx][i];
			    tpx=f[tpx][i];
			}
		}
		(ans2+=(tpsz*(tp-now)%mod+mod-tpj)%mod)%=mod;
		if(yy==lca) break;
		now+=g[yy][0];
		yy=f[yy][0];
	}
	printf("%lld\n",(ans+mod-ans2)%mod);
}

int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	init();
	work();
	return 0;
}
/*
4
2 1
3 2
1 3
4 3

2
1 1
2 2
*/
