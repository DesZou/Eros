#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
typedef long long ll;
const int N=505;
const int inf1=(int)1e9+7;
const ll inf=(ll)2e18;
int a[N],f[N][N],id[N];
ll ans[N][N];
int cmp(int x,int y){return a[x]<a[y];}
int main(){
    #ifndef ONLINE_JUDGE
        freopen("path.in","r",stdin);
        freopen("path.out","w",stdout);
    #endif
    int n,m,i,x,y,z,j,k,kk;
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++) scanf("%d",&a[i]),id[i]=i;
    for(i=1;i<=n;i++) for(j=1;j<=n;j++) f[i][j]=inf1,ans[i][j]=inf;
    for(i=1;i<=m;i++){
        scanf("%d %d %d",&x,&y,&z);
        f[x][y]=f[y][x]=z;
    }
    sort(id+1,id+n+1,cmp);
    for(kk=1;kk<=n;kk++){
        k=id[kk];
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                f[i][j]=min(f[i][j],max(f[i][k],f[k][j]));
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                if(a[k]>=a[i]&&a[k]>=a[j]&&f[i][j]<inf1) ans[i][j]=min(ans[i][j],(ll)f[i][j]*a[k]);
    }
    for(i=1;i<=n;i++,printf("\n"))
        for(j=1;j<=n;j++){
            if(i==j) printf("0 ");
            else if(ans[i][j]==inf) printf("-1 ");
            else printf("%lld ",ans[i][j]);
        }
    return 0;
}
