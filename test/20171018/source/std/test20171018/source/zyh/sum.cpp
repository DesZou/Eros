#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
//#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
#define fr(x) freopen(#x ".in","r",stdin);freopen(#x ".out","w",stdout)
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
using namespace std;
typedef long long ll;
ll ans=0,p;
int n;
ll fm(ll,int&,ll&);
int read();
int main()
{
	fr(sum);
	scanf("%d%lld",&n,&p);
	int x;
	ll sum=0;
	for(int i=1;i<=n;i++)
	{
		x=read();
		sum=fm(sum+1,x,p);
//		assert(sum>=0);
		ans=(ans+sum)%p;
	}
	printf("%lld\n",ans);
//	fprintf(stderr,"%.3f s\n",clock()*1.0/CLOCKS_PER_SEC);
	return 0;
}
ll fm(ll I,int &times,ll &mod)
{
	ll ret=0;
	while(times)
	{
		if(times&1) ret=(ret+I)%mod;
		times>>=1,I=(I+I)%mod;
//		assert(I>=0);
	}
	return ret;
}
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-'0',c=getchar();
	return x*f;
}