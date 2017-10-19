//Serene
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;
#define ll long long
const int maxn=2e5+10;
ll n,m,k,t,ans[maxn],a[maxn],lx[maxn],tot,tot2;

ll aa;char cc;
ll read() {
	aa=0;cc=getchar();
	while(cc<'0'||cc>'9') cc=getchar();
	while(cc>='0'&&cc<='9') aa=aa*10+cc-'0',cc=getchar();
	return aa;
}

ll ef(ll l,ll r,ll x) {
	if(x<a[l]) return -1;
	ll mid;
	while(l<r-1) {
		mid=(l+r)>>1;
		if(a[mid]<=x) l=mid;
		else r=mid;
	}
	return l;
}

struct Ask{
	ll l,r;int pos;
}ask[maxn];

bool cmp(const Ask& a,const Ask& b) {
	return a.r<b.r;
}

ll sz1[maxn],sz2[maxn];
void add(ll pos,ll x,ll* sz) {
	if(!pos) return;
	while(pos<=n) {
		sz[pos]+=x;
		pos+=(pos&-pos);
	}
}

ll q(ll pos,ll* sz) {
	ll rs=0;
	while(pos) {
		rs+=sz[pos];
		pos-=(pos&-pos);
	}
	return rs;
}

int main() {
//	freopen("sequence.in","r",stdin);
//	freopen("sequence.out","w",stdout);
	n=read();m=read();k=read();
	for(int i=1;i<=n;++i) {
		a[i]=read();
		a[i]=(a[i]>=m? 1:0)+a[i-1];
	}
	for(int i=1;i<=n;++i) lx[i]=ef(0,n,a[i]-k)+1;
	t=read();ll l,r,ff;
	for(int i=1;i<=t;++i) {
		l=read();r=read();ff=0;
		for(int j=l;j<=r;++j) for(int z=l-1;z<j;++z) if(a[j]-a[z]>=k) ff++;
		printf("%lld\n",ff);
	}
//	fclose(stdin);fclose(stdout);
	return 0;
}

