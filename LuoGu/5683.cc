#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdio>

template<class T> bool chkmin(T &a, const T &b) { return a > b? a = b, 1 : 0; }

const int N = 3e3 + 5;
const int Inf = (-1u >> 1) >> 2;

struct Edge { int nxt, to; } e[N * 2];

int head[N], f[N], g[N], h[N];

int n, m, s1, s2, t1, t2;

void insert(int u, int v) {
	static int idx = 0;
	e[++idx] = { head[u], v };
	head[u] = idx;
}

void bfs(int s, int dis[]) {
	static std::queue<int> q;
	std::fill(dis + 1, dis + 1 + n, Inf);
	dis[s] = 0;
	q.push(s);
	while (!q.empty()) {
		s = q.front(); q.pop();
		for (int i = head[s], t = e[i].to; i; i = e[i].nxt, t = e[i].to)
			if (chkmin(dis[t], dis[s] + 1)) q.push(t);
	}
}

int main() {
	std::ios::sync_with_stdio(false);

	std::cin >> n >> m;

	for (int i = 1, u, v; i <= m; ++i) {
		std::cin >> u >> v;
		insert(u, v);
		insert(v, u);
	}

	std::cin >> s1 >> t1 >> s2 >> t2;

	bfs(1, f);
	bfs(s1, g);
	bfs(s2, h);

	int ans = Inf;

	for (int i = 1; i <= n; ++i)
		if (f[i] + g[i] <= t1 &&
			f[i] + h[i] <= t2)
			chkmin(ans, f[i] + g[i] + h[i]);

	std::cout << (ans == Inf? -1 : m - ans) << std::endl;

	return 0;
}
