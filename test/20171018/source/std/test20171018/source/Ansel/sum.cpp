#include<bits/stdc++.h>
#define MAXN 100000+5
using namespace std;
int n,a[MAXN];
unsigned long long ans,p,E,II,m[MAXN];
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	scanf("%d%lld",&n,&p);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		E=0;m[i-1]=1;
		for(int j=i;j<=n;j++)
		{
			II=(m[j-1]*a[j])%p;
			m[j]=II;
			E+=II;E=E%p;
		}
		ans+=E;ans=ans%p;
	}
	printf("%lld",ans);
	return 0;
} 
