#include <cstdio>
#include <cstring>
#include <algorithm>

template <typename Tp>Tp Max(const Tp &a, const Tp &b) {return a > b ? a : b;}
template <typename Tp>Tp Min(const Tp &a, const Tp &b) {return a < b ? a : b;}

template <typename Tp>void Read(Tp &x) {
	Tp in = 0, f = 1; char ch = getchar();
	while(ch<'0' || ch>'9') {if(ch=='-') f = -1; ch = getchar();}
	while(ch>='0' && ch<='9') {in = in*10+ch-'0'; ch = getchar();}
	x = in*f;
}

typedef long long LL;

const int MOD = 1000000007;

const int SN = 500000 + 10;

LL ans, size;

int head[SN], cost[SN], num, n;

bool vis[SN];

struct Edge {
	int v, next;
}E[SN];

void Add(int u, int v, int w) {
	E[++num].v = v, E[num].next = head[u], head[u] = num, cost[num] = w;
}

void Dfs(int now, int d) {
	vis[now] = 1;
	for(int i = head[now]; i; i = E[i].next) {
		int to = E[i].v;
		if(vis[to]) continue;
		size ++;
		ans = (ans + cost[i] + d)%MOD;
		Dfs(to, (d+cost[i])%MOD);
	}
}

int main() {
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	
	int x = 0, y = 0;
	
	Read(n);

	for(int i = 1; i <= n; i++) {
		Read(x), Read(y);
		Add(i, x, y);
	}

	for(int i = 1; i <= n; i++) {
		size = 1;

		memset(vis, 0, sizeof vis);

		Dfs(i, 0);

		ans = (ans - (n-size) + MOD)%MOD;
	}

	printf("%lld\n", ans);

	return 0;
}
