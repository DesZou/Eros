//by Saramanda
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define For(i,_beg,_end) for(int i=(_beg),i##end=(_end);i<=i##end;++i)
#define Rep(i,_beg,_end) for(int i=(_beg),i##end=(_end);i>=i##end;--i)

template<typename T>T Max(const T &x,const T &y){return x<y?y:x;}
template<typename T>T Min(const T &x,const T &y){return x<y?x:y;}
template<typename T>int chkmax(T &x,const T &y){return x<y?(x=y,1):0;}
template<typename T>int chkmin(T &x,const T &y){return x>y?(x=y,1):0;}
template<typename T>void read(T &x){
	T f=1;char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
	for(x=0;ch>='0'&&ch<='9';ch=getchar())x=x*10+ch-'0';
	x*=f;
}

typedef long long LL;
const int maxn=500010,mod=1000000007;
int n,to[maxn],d[maxn];
int que[maxn],H,T,sz[maxn];
LL len[maxn],F[maxn],dis[maxn],ans;
bool vis[maxn],work[maxn],cir[maxn];

LL f(LL x){return x>=mod?x-mod:x;}
LL calc(int x){
	int num=sz[x]-1,beg=x;
	LL res=0;
	while(to[x]!=beg){
		res=f(res+len[x]*(num--)%mod);
		x=to[x];
	}
	return res;
}

int main(){
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	read(n);
	For(i,1,n){
		read(to[i]);
		read(len[i]);
		d[to[i]]++;
		if(to[i]==i){
			vis[i]=true;
			ans=f(ans-(n-1)+mod);
		}
	}
	For(i,1,n) if(!d[i])vis[que[++T]=i]=true;
	while(H<T){
		int x=que[++H];
		if(!--d[to[x]])vis[que[++T]=to[x]]=true;
	}
	For(i,1,n) if(!vis[i]&&!cir[i]){
		int x=i;cir[i]=true;
		sz[i]=1;
		while(to[x]!=i){
			dis[i]=f(dis[i]+len[x]);
			sz[i]++;
			cir[x=to[x]]=true;
		}
		LL tot=f(dis[i]+len[x]);
		x=i;
		while(to[x]!=i){
			dis[to[x]]=f(tot-len[x]+mod);
			sz[to[x]]=sz[i];
			x=to[x];
		}
		ans=f(ans-(LL)(sz[i])*(n-sz[i])%mod+mod);
	}
	For(i,1,n) if(!vis[i]&&!work[i]){
		F[i]=calc(i);
		int x=i;work[i]=true;
		while(to[x]!=i){
			F[to[x]]=(F[x]-(sz[x]-1)*len[x]%mod+dis[to[x]]+mod)%mod;
			work[x=to[x]]=true;
		}
	}
	Rep(i,T,1){
		int x=que[i];
		sz[x]=sz[to[x]]+1;
		F[x]=f(F[to[x]]+sz[to[x]]*len[x]%mod);
		ans=f(ans-(n-sz[x])+mod);
	}
	For(i,1,n) ans=f(ans+F[i]);
	printf("%lld\n",ans);
	return 0;
}
