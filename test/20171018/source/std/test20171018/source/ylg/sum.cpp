#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<queue>
#define nn 100011
using namespace std;
typedef long long lo;
lo f[nn],a[nn];
lo read()
{
	lo ans=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) {ans=ans*10+ch-'0';ch=getchar();}
	return ans*f;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	lo n,p,ans=0;
	n=read();p=read();
	for(int i=1;i<=n;i++)
	  a[i]=read();
	for(int i=n;i>=1;i--)
	  f[i]=(f[i+1]+1)*a[i]%p;
	for(int i=1;i<=n;i++)
	  ans=(ans+f[i])%p;
	printf("%lld",ans);
	return 0;
}
