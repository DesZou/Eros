#include <stdio.h>
#include <iostream>
#include <cstring>
typedef long long ll;
int n;
ll ans=0,mod,now,x;
using namespace std;

ll mult(ll x,ll y)
{
	ll rtn=0,tmp=x;
	while (y)
	{
		if (y&1) rtn=(rtn+tmp)%mod;
		tmp=(tmp+tmp)%mod,y>>=1;
	}
	return rtn;
}
int main()
{
	freopen ("sum.in","r",stdin);
	freopen ("sum.out","w",stdout);
	scanf ("%d %lld",&n,&mod);
	int i;now=0;
	for (i=1;i<=n;i++)
	{
		scanf ("%lld",&x);
		now=mult(now+1,x);
		ans=(ans+now)%mod;
	}
	printf ("%lld",ans);
	return 0;
}

