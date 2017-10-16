#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;

int n, m, e;

int dist[15][105][105], ans[2][105][105], cur;

void Floyd() {
	for (int t = 1; t <= 13; ++t) {
		for (int k = 1; k <= n; ++k)
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j)
					dist[t][i][j] = dist[t][j][i] = std::min(dist[t][i][j], dist[t - 1][i][k] + dist[t - 1][k][j]);
	}
	
	for (int i = 1; i <= n; ++i)
		ans[0][i][i] = 0;
	for (int t = 0; t <= 13; ++t) if ((e >> t) & 1) {
		cur ^= 1;
		memset(ans[cur], 0x3f, sizeof ans[cur]);
		for (int k = 1; k <= n; ++k)
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j)
					ans[cur][i][j] = ans[cur][j][i] = std::min(ans[cur][i][j], ans[cur ^ 1][i][k] + dist[t][k][j]);
	}
}

std::string fileName("graph");

int main(int argc, char *argv[]) {
	assert(argc >= 1);
	fileName += argv[1];
	
	freopen((fileName + ".in").c_str(), "r", stdin);
	freopen((fileName + ".out").c_str(), "w", stdout);
	
	memset(dist, 0x3f, sizeof dist);
	memset(ans, 0x3f, sizeof ans);
	
	scanf("%d%d%d", &n, &m, &e);
	for (int i = 1; i <= m; ++i) {
		static int u, v, w;
		
		scanf("%d%d%d", &u, &v, &w);
		dist[0][u][v] = dist[0][v][u] = w;
	}
	
	Floyd();
	
	int q; scanf("%d", &q);
	while (q--) {
		static int u, v;
		
		scanf("%d%d", &u, &v);
		printf("%d\n", ans[cur][u][v] == INF ? -1 : ans[cur][u][v]);
	}
	
	return 0;
}
