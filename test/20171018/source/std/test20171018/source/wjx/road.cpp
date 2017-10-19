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
LL ans;
int fl,n;

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
}

void init() {
    read(n);
    for(register int i=1;i<=n;i++) {
	    int u,v,w;
	    u=i; read(v); read(w);
	    if(w!=0) fl=1;
	    add(u,v,w);
	}
}

int vis[2050];
LL dis[2050];
void djkstra(int s) {
    memset(dis,-1,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[s]=0;
    for(;;) {
	    int k=0;
	    for(register int i=1;i<=n;i++) {
		    if(!vis[i]&&dis[i]!=-1&&(!k||dis[k]>dis[i]))
		        k=i;
 		}
 		if(!k) break; 
 		vis[k]=1;
 		for(register int i=fir[k];i;i=nxt[i]) if(!vis[to[i]]) {
		     if(dis[to[i]]==-1||dis[to[i]]>dis[k]+val[i])
		         dis[to[i]]=dis[k]+val[i];
		}
	}
	for(register int i=1;i<=n;i++)
	  (ans+=(dis[i]%mod+mod))%=mod;
}

void work() {
	if(n<=2000) {
		for(register int i=1;i<=n;i++)
	        djkstra(i);
	    printf("%lld\n",ans);
	}
	else if(!fl) {
		
	}
	else {
	
	}
}

int main()
{
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
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
