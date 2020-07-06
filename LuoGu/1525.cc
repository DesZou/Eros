/**
 *	luogu 1525
 *
 *	binary check anwser
 * */

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

const int N = 2e4 + 5;
const int M = 1e5 + 5;

struct Edge { int next, to, val; } e[M * 2];

int head[N], color[N];

int n, m;

void insert(int u, int v, int w) {
	static int ind = 0;
	e[++ind] = { head[u], v, w };
	head[u] = ind;
}

bool dfs(int it, int val) {
	for (int i = head[it]; i; i = e[i].next) if (e[i].val >= val) {
		if (!color[e[i].to]) {
			color[e[i].to] = color[it] ^ 3;
			if (!dfs(e[i].to, val)) return false;
		} else if (color[it] == color[e[i].to]) {
			return false;
		}
	}
	return true;
}

bool check(int val) {
	std::fill(color + 1, color + 1 + n, 0);
	
	for (int i = 1; i <= n; ++i) if (!color[i]) {
		color[i] = 1;
		if (!dfs(i, val)) return false;
	}

	return true;
}

int main() {
	std::ios::sync_with_stdio(false);

	std::cin >> n >> m;

	int l = 0, r = 0;

	for (int i = 1, u, v, w; i <= m; ++i) {
		std::cin >> u >> v >> w;
		insert(u, v, w);
		insert(v, u, w);
		r = std::max(r, w);
	}

	while (l < r) {
		int mid = (l + r) >> 1;
		if (check(mid))
			r = mid;
		else
			l = mid + 1;
	}

	std::cout << std::max(0, l - 1) << std::endl;

	return 0;
}
