#include <bits/stdc++.h>

typedef long long LL;

#define FOR(i, a, b) for (int i = (a), i##_END_ = (b); i <= i##_END_; i++)
#define DNF(i, a, b) for (int i = (a), i##_END_ = (b); i >= i##_END_; i--)

template <typename Tp> void in(Tp &x) {
	char ch = getchar(), f = 1; x = 0;
	while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if (ch == '-') ch = getchar(), f = -1;
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	x *= f;
}

template <typename Tp> Tp Max(const Tp &x, const Tp &y) {return x > y ? x : y;}
template <typename Tp> Tp Min(const Tp &x, const Tp &y) {return x < y ? x : y;}
template <typename Tp> bool chkmax(Tp &x, Tp y) {return x >= y ? 0 : (x=y, 1);}
template <typename Tp> bool chkmin(Tp &x, Tp y) {return x <= y ? 0 : (x=y, 1);}

const int MAXN = 500010, MOD = 1000000007;

int n;
int cnt, head[MAXN], data[MAXN], nxt[MAXN], flow[MAXN];

bool vis[MAXN];

int f[MAXN], g[MAXN], fa[MAXN];
int belong[MAXN]; bool in_stack[MAXN];
int stack[MAXN], low[MAXN], dfn[MAXN], Index, sz_b[MAXN];
int sz[MAXN];

int ans; int tot;
int ORZ_QYS[MAXN];

void add(int x, int y, int z)
{
	nxt[cnt] = head[x]; data[cnt] = y; flow[cnt] = z; head[x] = cnt++;
}

void dfs(int now)
{
	dfn[now] = low[now] = ++Index;
	in_stack[now] = true; stack[++stack[0]] = now;

	for (int i = head[now]; i != -1; i = nxt[i]) {
		fa[data[i]] = now;
		if (!dfn[data[i]]) {
			dfs(data[i]);
			chkmin(low[now], low[data[i]]);
		}
		else if (in_stack[data[i]]) {
			chkmin(low[now], dfn[data[i]]);
		}
	}

	if (dfn[now] == low[now]) {
		++belong[0];
		belong[now] = belong[0];
		in_stack[now] = false;
		sz_b[belong[0]] = 1;
		while (stack[stack[0]] != now) {
			belong[stack[stack[0]]] = belong[0];
			in_stack[stack[stack[0]]] = false;
			stack[0]--;
			sz_b[belong[0]]++;
		}
		stack[0]--;
	}
}

void solve(int now)
{
	vis[now] = true;
	
	if (sz_b[belong[now]] > 1) {
		for (int i = head[now]; i != -1; i = nxt[i]) {
			if (!vis[data[i]] && belong[data[i]] == belong[now])
				solve(data[i]);
			else if (!vis[data[i]]) {
				solve(data[i]);
				int tmp = (f[data[i]] + 1ll * sz[data[i]] * flow[i] % MOD) % MOD;
				f[now] = (f[now] + tmp) % MOD;
			}
		}
		ans = (ans + f[now]) % MOD;
	}
	
	else {
		sz[now] = 1;
		for (int i = head[now]; i != -1; i = nxt[i]) {
			solve(data[i]);
			sz[now] += sz[data[i]];
			int tmp = (f[data[i]] + 1ll * sz[data[i]] * flow[i] % MOD) % MOD;
			f[now] = (f[now] + tmp) % MOD;
		}
		ans = (ans + f[now]) % MOD;
		tot = (tot + sz[now] - 1) % MOD;
	}
}

int number = 0;

int check_two(int now, int st)
{
	ORZ_QYS[++ORZ_QYS[0]] = now;
	
	sz[now] = 1;
	number++;
	
	for (int i = head[now]; i != -1; i = nxt[i])
		if (belong[data[i]] != belong[now])
			sz[now] += sz[data[i]];

	tot = (tot + sz[now] - 1) % MOD;

	for (int i = head[now]; i != -1; i = nxt[i]) {
		if (belong[data[i]] == belong[now]) {
			if (data[i] == st) return (g[now] = flow[i]);
			int tmp = check_two(data[i], st);
			g[now] = flow[i];
			return (tmp + flow[i]) % MOD;
		}
	}
}

int main()
{
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
	
	in(n);
	memset(head, -1, sizeof head);
	
	FOR(i, 1, n) {
		int x, y;
		in(x); in(y);

		if (i == x) continue;
		add(x, i, y);
	}

	FOR(i, 1, n) if (!dfn[i]) dfs(i);

	FOR(i, 1, n) if (sz_b[belong[i]] > 1 && !vis[i]) {
		solve(i);
		number = 0;
		ORZ_QYS[0] = 0;
		int all = check_two(i, i), now = 0;

		FOR(j, 2, ORZ_QYS[0])
			now = (now + 1ll * (j - 1) * g[ORZ_QYS[j]] % MOD) % MOD;

		FOR(j, 1, ORZ_QYS[0]) {
			ans = (ans + 1ll * f[ORZ_QYS[j]] * (number - 1) % MOD) % MOD;
			ans = (ans + 1ll * now * sz[ORZ_QYS[j]] % MOD) % MOD;
			now = (now - all) % MOD;
			now = (now + g[ORZ_QYS[j]]) % MOD;
			now = (now + 1ll * g[ORZ_QYS[j]] * (ORZ_QYS[0] - 1) % MOD) % MOD;
			now = (now % MOD + MOD) % MOD;

			tot = (tot + 1ll * sz[ORZ_QYS[j]] * (ORZ_QYS[0] - 1) % MOD) % MOD;
		}
		//check_thr(i, i, all);
	}

	FOR(i, 1, n) if (!vis[i] && !fa[i]) solve(i);

	int ret = ((ans + tot) % MOD - (1ll * n * (n - 1)) % MOD);

	ret = (ret % MOD + MOD) % MOD;

	printf("%d\n", ret);
	
	return 0;
}
