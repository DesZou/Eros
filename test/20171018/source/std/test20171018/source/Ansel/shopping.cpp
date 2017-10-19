#include<bits/stdc++.h>
#define MAXN 100000+5
using namespace std;
int n,m;
struct SHOP
{int i,w,p;}a[MAXN];
bool cmp(SHOP a,SHOP b)
{
	if(a.w/a.p>b.w/b.p)return 1;
	return a.p>b.p;
	return 1;
}
void shop(int k)
{
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		while(k>=a[i].p)
		{
			ans+=a[i].w;
			k=k-a[i].p;
		}
	}
	printf("%d\n",ans);
	return;
}
int main()
{
	freopen("shopping.in","r",stdin);
	freopen("shopping.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		a[i].i=i;
		scanf("%d%d",&a[i].w,&a[i].p);
	}
	sort(a+1,a+n+1,cmp);
	while(m--)
	{
		int flag;
		scanf("%d",&flag);
		if(flag==1)
		{
			int x,w,p;
			scanf("%d%d%d",&x,&w,&p);
			for(int i=1;i<=n;i++)
			{
				if(a[i].i==x)
				{a[i].w=w;a[i].p=p;}
			}
			sort(a+1,a+n+1,cmp);
		}
		else
		{
			int k;
			scanf("%d",&k);
			shop(k);
		}
	}
	return 0;
} 
