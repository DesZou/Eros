#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <queue>
#define THE_BEST_PONY "Rainbow Dash"

using namespace std;
typedef long long LL;
const int maxn=5200,mod=1000000007,INF=~0u>>1;

struct hq{
	int u;
	LL d;
	
	bool operator <(const hq &x) const{
		return d>x.d;
	}
};

int n;
int to[maxn],w[maxn];
LL dis[maxn][maxn],ans;
bool vis[maxn][maxn];

int main(){
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	scanf("%d",&n);
	if(n>maxn) printf("%lld",-1ll*n*n%mod);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&to[i],&w[i]);
	for(int s=1;s<=n;s++){
		for(int i=1;i<=n;i++) dis[s][i]=INF;
		priority_queue<hq> pq;
		dis[s][s]=0;
		pq.push((hq){s,dis[s][s]});
		while(!pq.empty()){
			int cur=pq.top().u; pq.pop();
			if(vis[s][cur]) continue;
			else vis[s][cur]=true;
			if(dis[s][to[cur]]>dis[s][cur]+w[cur]){
				dis[s][to[cur]]=dis[s][cur]+w[cur];
				pq.push((hq){to[cur],dis[s][to[cur]]});
			}
		}
		for(int i=1;i<=n;i++){
			ans+=(dis[s][i]==INF?-1:dis[s][i]);
			if(ans<0) ans+=mod;
			ans%=mod;
		}
	}
	printf("%lld",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}

