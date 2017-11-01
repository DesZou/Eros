#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <ctime>
#define lowbit(x) (x&-x)

using namespace std;

typedef long long ll;

int c[100005],w[100005],b[100005];

int main() {
  freopen("5.in","r",stdin);
  freopen("5.out","w",stdout);
  int n,m;
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++) scanf("%d",&c[i]);
  for(int i=1;i<=n;i++) scanf("%d",&w[i]);
  for(int i=1;i<=m;i++) {
  	int kind,x,y;
  	scanf("%d%d%d",&kind,&x,&y);
  	if (kind==1) c[x]=y;
  	else {
  		for(int j=x;j<=y;j++) b[j]=c[j];
  		sort(b+x,b+y+1);
  		ll ans=0;
  		for(int j=x;j<=y;j++) 
  		  if (j==x||b[j]!=b[j-1]) ans+=w[b[j]];
  		printf("%lld\n",ans);
	  }
  }
  return 0;
}
