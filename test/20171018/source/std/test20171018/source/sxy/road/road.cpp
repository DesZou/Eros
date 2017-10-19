//Serene
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;
#define ll long long
const int maxn=5e5+10;
const ll mod=1e9+7,INF=1e9+6;
int n;bool k1;
ll dis[maxn],ans=0;

ll aa;char cc;
ll read() {
	aa=0;cc=getchar();
	while(cc<'0'||cc>'9') cc=getchar();
	while(cc>='0'&&cc<='9') aa=aa*10+cc-'0',cc=getchar();
	return aa;
}

int d[maxn];ll v[maxn];
void add(int x,int y,ll z) {
	d[x]=y;v[x]=z; if(z) k1=1;
}

int fir[maxn],nxt[maxn],to[maxn],r[maxn],e=0;
int ff[maxn],nn[maxn],tt[maxn],ee=0;
void bld(int x,int y) {
	to[++e]=y;nxt[e]=fir[x];fir[x]=e;
	tt[++ee]=x;nn[ee]=ff[y];ff[y]=ee;
	r[x]++;
}

int zz[maxn],dep[maxn],top[maxn],t=0;
int id[maxn],sum[maxn],totid;
bool vis[maxn],inz[maxn];
void tj(int pos) {
	zz[++t]=pos; vis[pos]=inz[pos]=1; top[pos]=pos;
	int z=d[pos];
	if(z!=pos) {
		if(!vis[z]) dep[z]=dep[pos]+1,tj(z);
		if(inz[z]) top[pos]= dep[top[pos]] <= dep[top[z]] ? top[pos] : top[z];
	}
	if(top[pos]==pos) {
		totid++;
		do{
			inz[zz[t]]=0;
			id[zz[t--]]=totid;
			sum[totid]++;
		}while(t&&zz[t+1]!=pos);
	}
}

void tp() {
	int s=1,t=0,x,y,z;
	for(int i=1;i<=totid;++i) if(!r[i]) zz[++t]=i;
	while(s<=t) {
		x=zz[s++];
		for(y=fir[x];y;y=nxt[y]) {
			r[z=to[y]]--;
			if(!r[z]) zz[++t]=z;
		}
	}
	while(t) {
		x=zz[t--];
		for(y=ff[x];y;y=nn[y]) {
			z=tt[y];
			sum[z]+=sum[x];
		}
	}
}

void bfs(int pos) {
	for(int i=1;i<=n;++i) dis[i]=1e14;
	dis[pos]=0;
	int s=1,t=0,x,z; zz[++t]=pos;
	while(s<=t) {
		x=zz[s++];z=d[x];
		dis[z] > dis[x]+v[x]? zz[++t]=z,dis[z]=dis[x]+v[x]:0;
	}
	for(int i=1;i<=n;++i) (ans+=dis[i]==1e14? INF:dis[i])%=mod;
}

int main() {
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	n=read(); int x; ll y;
	for(int i=1;i<=n;++i) {
		x=read();y=read();
		add(i,x,y);
	}
	if(n<=2000) {
		for(int i=1;i<=n;++i) bfs(i);
		printf("%lld",ans);
	}
	else {
		for(int i=1;i<=n;++i) if(!vis[i]) t=0,tj(i);
		for(int i=1;i<=n;++i) if(id[i]!=id[d[i]]) bld(id[i],id[d[i]]);
		tp();
		for(int i=1;i<=n;++i) ans=(ans+sum[id[i]]-n+mod)%mod;
		if(!k1) printf("%lld",ans);
		else {
			for(int i=1;i<=n;++i) ans=(ans+v[i]*(sum[id[i]]-1)%mod)%mod;
			printf("%lld",ans);
		}
	}
	fclose(stdin);fclose(stdout);
	return 0;
}
/*
4
2 1
3 2
1 3
2 3

3
2 1
1 0
3 0
*/

