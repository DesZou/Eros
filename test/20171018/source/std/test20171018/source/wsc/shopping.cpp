#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>
#include <algorithm>
#define THE_BEST_PONY "Rainbow Dash"

using namespace std;
typedef long long LL;
const int maxn=100000;

struct Goods{
	int w,p;
	
	bool operator < (const Goods &x) const{
		if(w<x.w) return true;
		if(w>x.w) return false;
		return p>x.p;
	}
}g[maxn];

struct SegTree{
	Goods MX[maxn<<2];
	int L[maxn<<2],R[maxn<<2];
	
	void BuildTree(int x,int l,int r){
		L[x]=l; R[x]=r;
		if(l==r){
			MX[x]=g[l];
			return;
		}
		int M=(L[x]+R[x])>>1;
		BuildTree(x<<1,l,M);
		BuildTree(x<<1|1,M+1,r);
		MX[x]=max(MX[x<<1],MX[x<<1|1]);
		return;
	}
	
	void UpdateTree(int x,int p,Goods v){
		if(L[x]==R[x]&&L[x]==p){
			MX[x]=v;
			return;
		}
		int M=(L[x]+R[x])>>1;
		if(p<=M) UpdateTree(x<<1,p,v);
		if(M<p) UpdateTree(x<<1|1,p,v);
		MX[x]=max(MX[x<<1],MX[x<<1|1]);
		return;
	}
	
	Goods QueryTree(int x,int l,int r,int k){
		if(l<=L[x]&&R[x]<=r&&MX[x].p<=k) return MX[x];
		else{
			Goods re; re.w=re.p=0;
			if(L[x]<R[x]){
				int M=(L[x]+R[x])>>1;
				if(l<=M) re=max(re,QueryTree(x<<1,l,r,k));
				if(M<r) re=max(re,QueryTree(x<<1|1,l,r,k));
			}
			return re;
		} 
	}
}S;

int n,m;

int main(){
	freopen("shopping.in","r",stdin);
	freopen("shopping.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d%d",&g[i].w,&g[i].p);
	S.BuildTree(1,1,n);
	while(m--){
		int op;
		scanf("%d",&op);
		if(op==1){
			int x,w,p;
			scanf("%d%d%d",&x,&w,&p);
			S.UpdateTree(1,x,(Goods){w,p});
		}
		else{
			int k;
			LL ans=0;
			scanf("%d",&k);
			while(k){
				Goods b=S.QueryTree(1,1,n,k);
				if(b.p==0) break;
				ans+=1ll*k/b.p*b.w;
				k%=b.p;
			}
			printf("%lld\n",ans);
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}

