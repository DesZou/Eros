//El Psy Congroo
#include <cstdio>
#include <cmath>
#include <queue>
#include <algorithm>
#include <cstring>
#include <climits>
#define LL long long
#define MAXN 500
#define MOD 1000000007
using namespace std;
int n,to[MAXN];
LL ans,g[MAXN][MAXN];
int main()
{
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);

  scanf("%d",&n);
  for(int i=1;i<=n;i++)
  	for(int j=1;j<=n;j++)
  		g[i][j]=(1<<30);
  for(int i=1;i<=n;i++)
  {
  	scanf("%d",&to[i]);
  	scanf("%lld",&g[i][to[i]]);
  }

  for(int k=1;k<=n;k++)
  {
  	for(int i=1;i<=n;i++) if(i!=k)
  	{
  		for(int j=1;j<=n;j++) if(j!=i&&j!=k)
  		{
  			if(g[i][j]>g[i][k]+g[k][j])
  				g[i][j]=g[i][k]+g[k][j];
  		}
  	}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			//printf("%lld ",g[i][j]);
			if(i!=j){
				if(g[i][j]<=1000000000) ans=(ans+g[i][j])%MOD;
				else ans=(ans-1+MOD)%MOD;
			}
		}
		//printf("\n");
	}
	printf("%lld\n",ans);
	return 0;
}
/*
4
2 1
3 2
1 3
4 3
*/
