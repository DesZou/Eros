#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
int M=100000;
int irand(){return rand()<<15|rand();}
int main(){
    #ifndef ONLINE_JUDGE
        freopen("segment.in","w",stdout);
    #endif
    int n=200,m=200,q=200,i,c,l,r,x;
    srand(time(0));
    printf("%d %d %d\n",n,m,q);
    for(i=1;i<=n;i++) printf("%d ",irand()%M+1);printf("\n");
    for(i=1;i<=m;i++){
        c=irand()%2+1;
        l=irand()%n+1;
        r=irand()%n+1;
        if(c==1) M=100;
        else M=100000;
        x=irand()%M+1;
        if(l>r) swap(l,r);
        printf("%d %d %d %d\n",c,l,r,x);
    }
    for(i=1;i<=q;i++){
        l=irand()%n+1;
        r=irand()%n+1;
        if(l>r) swap(l,r);
        printf("%d %d\n",l,r);
    }
    return 0;
}
