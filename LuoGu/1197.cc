/**
 *	luogu 1197
 *
 *	union-find set
 *	reverse the events' order
 *
 * **/

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

const int N = 4e5 + 5;

int n, m, k;

int idx;

int atk[N];
int fa[N];
int ans[N];
int head[N];

bool destroyed[N];

struct Edge { int a, b, next; } e[N];

int find(int x) {
	return fa[x] == x? x : fa[x] = find(fa[x]);
}

int main() {
	std::ios::sync_with_stdio(false);

	std::cin >> n >> m;

	for (int i = 1; i < n; ++i) fa[i] = i;

	for (int a, b, i = 1; i <= m; ++i) {
		std::cin >> a >> b;
		e[i] = { a, b, head[a] };
		e[i + m] = { b, a, head[b] };
		head[a] = i;
		head[b] = i + m;
	}

	std::cin >> k;

	for (int i = 1; i <= k; ++i) {
		std::cin >> atk[i];
		destroyed[atk[i]] = true;
	}

	int cnt = n - k;

	for (int i = 1; i <= m; ++i) if (!destroyed[e[i].a] && !destroyed[e[i].b]) {
		int u = find(e[i].a);
		int v = find(e[i].b);
		if (u != v) {
			--cnt;
			fa[u] = v;
		}
	}

	ans[k + 1] = cnt;

	for (int i = k; i > 0; --i) {
		destroyed[atk[i]] = false;
		++cnt;
		for (int j = head[atk[i]]; j; j = e[j].next)
			if (!destroyed[e[j].b]) {
				int u = find(atk[i]);
				int v = find(e[j].b);
				if (u != v) {
					--cnt;
					fa[u] = v;
				}
			}
		ans[i] = cnt;
	}

	for (int i = 1; i <= k + 1; ++i) std::cout << ans[i] << std::endl;

	return 0;
}
