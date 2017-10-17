#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
const int N=505,M=(int)1e9;
int used[N][N],a[N];
int irand(){return rand()<<15|rand();}
int main(){
    #ifndef ONLINE_JUDGE
        freopen("path.in","w",stdout);
    #endif
    int n=20,m=50,i,x,y;
    printf("%d %d\n",n,m);
    srand(time(0));
    for(i=1;i<=n;i++) printf("%d ",irand()%M+1);printf("\n");
    for(i=1;i<=m;i++){
        do{
            x=irand()%n+1;
            y=irand()%n+1;
        }while(x==y||used[x][y]);
        used[x][y]=used[y][x]=1;
        printf("%d %d %d\n",x,y,irand()%M+1);
    }
    return 0;
}
