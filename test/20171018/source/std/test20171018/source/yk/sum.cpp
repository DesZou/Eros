#include<iostream>
#include<cstdio>
using namespace std;
long long getint()
{
	long long ans=0;char ch;
	do{ch=getchar();}while(ch<'0'||ch>'9');
	ans=ch-'0';
	while(isdigit(ch=getchar()))ans=ans*10+ch-'0';
	return ans;
}
long long mod;
long long qmul(long long x,long long y)
{
	long long ans=0;
	while(y)
	{
		if(y&1)
		  ans=(ans+x)%mod;
		x=(x+x)%mod;
		y>>=1;
	}
	return ans;
}
long long a[100001];
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n;
	n=getint();mod=getint();
	for(int i=1;i<=n;i++)
	  a[i]=getint();
	long long ans=0,mid=1;
	for(int i=1;i<=n;i++)
	{
		ans=(ans+qmul(a[i],mid))%mod;
		mid=(qmul(a[i],mid)+1)%mod;
	}
	cout<<ans;
}
