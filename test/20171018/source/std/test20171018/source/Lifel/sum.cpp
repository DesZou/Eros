#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
typedef long long ll;
ll a[N],p,n;
ll f[N],s[N];
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	scanf("%lld%lld",&n,&p);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		f[i]=0;
		s[i]=1;
	}
	f[1]=a[1];s[1]=a[1];
	for(int i=2;i<=n;i++)
	{
		f[i]=(f[i-1]+(s[i-1]*a[i])%p+a[i])%p;
		s[i]=((s[i-1]*a[i])%p+a[i])%p;
	}
	printf("%lld\n",f[n]);
	return 0;
	
}
