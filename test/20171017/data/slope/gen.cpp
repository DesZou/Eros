#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
const int M=(int)1e7;
int used[M+10];
int irand(){return rand()<<15|rand();}
int main(){
    #ifndef ONLINE_JUDGE
        freopen("slope.in","w",stdout);
    #endif
    int n=100,i,x;
    srand(time(0));
    printf("%d\n",n);
    for(i=1;i<=n;i++){
        do{x=irand()%M+1;}while(used[x]);used[x]=1;
        printf("%d %d\n",x,irand()%M+1);
    }
    return 0;
}
