//El Psy Congroo
#include <cstdio>
#include <cmath>
#include <queue>
#include <algorithm>
#include <cstring>
#include <climits>
#define LL long long
#define MAXN 200000
using namespace std;
int n;
LL p,a[MAXN],ans,sum;

LL ksc(LL a,LL b,LL mod)
{
	LL ans=0;
	while(b) 
	{
		if(b&1) ans=(ans+a)%mod;
		a=(a+a)%mod;
		b>>=1;
	}
	return ans;
}

int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
  scanf("%d%lld",&n,&p);
  for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
  
  for(int i=n;i>=1;i--)
  {
  	sum=ksc((sum+1),a[i],p);
  	ans=(ans+sum)%p;
  }
  printf("%lld\n",ans);
	return 0;
}
