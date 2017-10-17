#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
typedef double db;
typedef long long ll;
const int N=100010;
int a[N];
ll sum1[N],sum2[N],siz2[N];
db ans[N];
int main(){
    #ifndef ONLINE_JUDGE
        freopen("segment.in","r",stdin);
        freopen("segment.out","w",stdout);
    #endif
    int n,m,q,i,c,l,r,x;
    ll s1=0,s2=0,s3=0;
    scanf("%d %d %d",&n,&m,&q);
    for(i=1;i<=n;i++) scanf("%d",&a[i]);
    for(i=1;i<=m;i++){
        scanf("%d %d %d %d",&c,&l,&r,&x);
        if(c==1){
            sum1[l]+=x;sum1[r+1]-=x;
        }
        else{
            sum2[l]+=x;sum2[r+1]-=x;
            siz2[l]++;siz2[r+1]--;
        }
    }
    for(i=1;i<=n;i++){
        s1+=sum1[i];
        s2+=sum2[i];
        s3+=siz2[i];
        if(s3==0) ans[i]=a[i]+s1+ans[i-1];
        else ans[i]=1.0*s2/s3+1.0*s1/(s3+1)+ans[i-1];
    }
    for(i=1;i<=q;i++){
        scanf("%d %d",&l,&r);
        printf("%.3lf\n",ans[r]-ans[l-1]);
    }
    return 0;
}
