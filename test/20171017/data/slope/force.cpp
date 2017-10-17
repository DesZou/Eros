#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
typedef double db;
const int N=500010;
struct P{
    int x,y;
    bool operator<(const P& a)const{
        return x<a.x;
    }
}a[N];
int main(){
    #ifndef ONLINE_JUDGE
        freopen("slope.in","r",stdin);
        freopen("force.out","w",stdout);
    #endif
    int i,j,n;
    db ans=-(int)2e9;
    scanf("%d",&n);
    for(i=1;i<=n;i++) scanf("%d %d",&a[i].x,&a[i].y);
    for(i=1;i<n;i++)
    for(j=i+1;j<=n;j++)
    ans=max(ans,1.0*(a[i].y-a[j].y)/(a[i].x-a[j].x));
    printf("%.3lf\n",ans);
    return 0;
}
