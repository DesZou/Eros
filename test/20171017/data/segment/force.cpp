#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
typedef double db;
const int N=100010;
db ans[N];
int a[N],b[N],op[N][4],id[N],lf[N],rt[N];
int n,m,q;
void calc(){
    int i,c,l,r,x,j;
    //for(i=1;i<=m;i++) printf("%d ",id[i]);printf("\n");
    for(i=1;i<=n;i++) b[i]=a[i];
    for(i=1;i<=m;i++){
        c=op[id[i]][0];l=op[id[i]][1];r=op[id[i]][2];x=op[id[i]][3];
        if(c==1) for(j=l;j<=r;j++) b[j]+=x;
        else for(j=l;j<=r;j++) b[j]=x;
    }
    //printf("%d\n",b[1]);
    for(i=1;i<=q;i++)
        for(j=lf[i];j<=rt[i];j++)
            ans[i]+=b[j];
}
void dfs(int x){
    if(x>m){calc();return;}
    for(int i=x;i<=m;i++){
        swap(id[x],id[i]);
        dfs(x+1);
        swap(id[x],id[i]);
    }
}
int main(){
    #ifndef ONLINE_JUDGE
        freopen("segment4.in","r",stdin);
        freopen("force.out","w",stdout);
    #endif
    int i,j;
    scanf("%d %d %d",&n,&m,&q);
    for(i=1;i<=n;i++) scanf("%d",&a[i]);
    for(i=1;i<=m;i++)
        scanf("%d %d %d %d",&op[i][0],&op[i][1],&op[i][2],&op[i][3]);
    for(i=1;i<=m;i++) id[i]=i;
    for(i=1;i<=q;i++)
        scanf("%d %d",&lf[i],&rt[i]);
    dfs(1);
    for(i=1;i<=q;i++){
        for(j=1;j<=m;j++) ans[i]/=j;
        printf("%.3lf\n",ans[i]);
    }
    return 0;
}
