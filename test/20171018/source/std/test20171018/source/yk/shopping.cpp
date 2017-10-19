#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int mod=1e9+7;
int getint()
{
	int ans=0;char ch;
	do{ch=getchar();}while(ch<'0'||ch>'9');
	ans=ch-'0';
	while(isdigit(ch=getchar()))ans=ans*10+ch-'0';
	return ans;
}
struct T
{
	int x,y;
	void in()
	{
		x=getint();y=getint();
	}
}a[3000],b[3000];
bool cmp(const T& x,const T& y)
{
	return x.x>y.x;
}
int main()
{
	freopen("shopping.in","r",stdin);
	freopen("shopping.out","w",stdout);
	int n,m;
	n=getint();m=getint();
	for(int i=1;i<=n;i++)
	  a[i].in();
	for(int i=1;i<=m;i++)
	{
		int mrk=getint();
		if(mrk==1)
		  a[getint()].in();
		else
		{
			int x=getint();
			for(int j=1;j<=n;j++)
			  b[j]=a[j];
			sort(b+1,b+n+1,cmp);
			long long ans=0;
			for(int j=1;j<=n;j++)
			{
				ans+=x/b[j].y*b[j].x;
				x%=b[j].y;
			}
			cout<<ans<<"\n";
		}
	}
}

