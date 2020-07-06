/**
 *	luogu 2024
 *
 *	triple node union-find set
 *
 *	using triple node to describe complicated relations
 * */

#include <iostream>
#include <cstdio>
#include <algorithm>

const int N = 5e4 + 5;

int fa[N * 3];

int find(int x) {
	return x == fa[x]? x : fa[x] = find(fa[x]);
}

int main() {
	std::ios::sync_with_stdio(false);

	int n, k;

	std::cin >> n >> k;

	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
		fa[i + n] = i + n;
		fa[i + 2 * n] = i + 2 * n;
	}

	int ans = 0;

	for (int i = 1, c, x, y, u, v; i <= k; ++i) {
		std::cin >> c >> x >> y;
		if (x > n || y > n) { ++ans; continue; }
		if (c == 1) {
			u = find(x);
			v = find(y + n);
			if (u == v) { ++ans; continue; }
			u = find(x + n);
			v = find(y);
			if (u == v) { ++ans; continue; }
			u = find(x);
			v = find(y);
			fa[u] = v;
			u = find(x + n);
			v = find(y + n);
			fa[u] = v;
			u = find(x + 2 * n);
			v = find(y + 2 * n);
			fa[u] = v;
		} else {
			u = find(x);
			v = find(y);
			if (u == v) { ++ans; continue; }
			u = find(y);
			v = find(x + n);
			if (u == v) { ++ans; continue; }
			u = find(x);
			v = find(y + n);
			fa[u] = v;
			u = find(x + n);
			v = find(y + 2 * n);
			fa[u] = v;
			u = find(x + 2 * n);
			v = find(y);
			fa[u] = v;
		}
	}

	std::cout << ans << std::endl;

	return 0;
}
