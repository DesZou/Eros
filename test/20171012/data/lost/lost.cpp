#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;

const int MAXN = 5e5+5;

ll a[MAXN], p[MAXN], d[MAXN], n;
ll j[MAXN][20], ans[MAXN];
vector<int> c[MAXN];

void dfs(int u, int v) {
	d[u] = (u == 0) ? 0 : d[v]+1;
	
	if (u != 0) {
		int at = p[u];
		for (int i = 19; i >= 0; --i) {
			int to = j[at][i];
			if (to == 0)
				continue;
			ll cur1 = a[to]-a[u], cur2 = -d[to]+d[u];
			ll nex1 = a[j[to][0]]-a[u], nex2 = -d[j[to][0]]+d[u];

			if (nex1*cur2 <= nex2*cur1) {
				at = j[to][0]; i++;
			}
		}
		int to = at;
		if (to != 0) {
    		ll cur1 = a[to]-a[u], cur2 = -d[to]+d[u];
	    	ll nex1 = a[j[to][0]]-a[u], nex2 = -d[j[to][0]]+d[u];
		    if (nex1*cur2 <= nex2*cur1)
			    at = j[to][0];
		}

		ans[u] = at;
		j[u][0] = at;
		for (int i = 1; i <= 19; ++i)
			j[u][i] = j[j[u][i-1]][i-1];
	}
}

inline void get(ll &x) {
	char c = getchar(); x = 0;
	while (c < '0' || c > '9') c = getchar();
	while ('0' <= c && c <= '9') x = x * 10 + c - '0', c = getchar();
}

int main() {
	get(n);
	for (int i = 0; i < n; ++i) get(a[i]);
	for (int i = 1; i < n; ++i) {
		get(p[i]); p[i]--;
		c[p[i]].push_back(i);
	}

	p[0] = -1;
	
	for (int i = 0; i < n; ++i)
		dfs(i, p[i]);

	for (int i = 1; i < n; ++i)
		printf("%.10lf\n", double(a[ans[i]] - a[i]) / (d[i] - d[ans[i]]));
}