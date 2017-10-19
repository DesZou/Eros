#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10,inf=0x3fffffff;
struct Point
{
	int x,y;
	bool operator <(const Point &rhs)const {
		return rhs.x>x;
	}
}a[N];
int n;
double K(int x1,int y1,int x2,int y2){return double(y1*1.0000-y2*1.0000)/double(x1*1.0000-x2*1.0000);}
int main()
{
	freopen("slope.in","r",stdin);
	freopen("slope.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+1+n);
	double ans=-inf;
	for(int i=1;i<n;i++){ans=max(ans,K(a[i].x,a[i].y,a[i+1].x,a[i+1].y));}
	printf("%.3lf",ans);
	return 0;
}
