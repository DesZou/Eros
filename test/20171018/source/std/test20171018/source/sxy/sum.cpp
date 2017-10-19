//Serene
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;
#define ll long long
const int maxn=1e5+10;
ll n,mod,a[maxn],now,ans;

ll aa;char cc;
ll read() {
	aa=0;cc=getchar();
	while(cc<'0'||cc>'9') cc=getchar();
	while(cc>='0'&&cc<='9') aa=aa*10+cc-'0',cc=getchar();
	return aa;
}

ll rs;
ll f(ll x,ll k) {
	rs=0;
	while(k) {
		if(k&1) (rs+=x)%=mod;
		k>>=1; x=(x+x)%mod;
	}
	return rs;
}

int main() {
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	n=read();mod=read();
	for(int i=1;i<=n;++i) a[i]=read();
	for(int i=1;i<=n;++i) {
		now=f(now+1,a[i]);
		(ans+=now)%=mod;
	}
	printf("%lld",ans);
	fclose(stdin);fclose(stdout);
	return 0;
}

