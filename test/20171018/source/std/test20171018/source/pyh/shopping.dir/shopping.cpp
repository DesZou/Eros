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

const int MAXN = 100010;
const int inf = 0x3f3f3f3f;

using std::multiset;

multiset<int>value[MAXN << 1];

int n, m;
int tot = 0;
int w[MAXN], p[MAXN];

int minx[MAXN << 3];
int opt[MAXN][4], all[MAXN << 1], to[MAXN << 1], pos[MAXN << 1];

void update(int now)
{
	minx[now] = Min(minx[now << 1], minx[now << 1 | 1]);
}

void build(int now, int l, int r)
{
	if (l == r) {
		assert(value[l].begin() != value[l].end());
		minx[now] = *value[l].begin();
		pos[l] = now;
		return;
	}
	int mid = (l + r) >> 1;
	build(now << 1, l, mid); build(now << 1 | 1, mid + 1, r);
	update(now);
}

int L, R, X;

void modify(int now, int l, int r)
{
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (L <= mid) modify(now << 1, l, mid);
	else modify(now << 1 | 1, mid + 1, r);
	update(now);
}

int query(int now, int l, int r)
{
	if (L <= l && r <= R) {
		if (l == r) return l;
		int mid = (l + r) >> 1;
		if (minx[now << 1 | 1] > X)
			return query(now << 1, l, mid);
		else return query(now << 1 | 1, mid + 1, r);
	}

	int mid = (l + r) >> 1;
	if (R <= mid) return query(now << 1, l, mid);
	if (mid < L) return query(now << 1 | 1, mid + 1, r);
	
	int x1 = query(now << 1, l, mid), x2 = query(now << 1 | 1, mid + 1, r);
	
	if (minx[pos[x2]] <= X) return x2;
	else return x1;
}

void find(int x)
{
	LL ret = 0;
	int now = all[0] + 1;
	
	while (true) {
		if (now == 1) break;
		
		L = 1, R = now - 1, X = x;
		now = query(1, 1, all[0]);

		int tmp = minx[pos[now]];

		if (tmp > x) break;
		ret += 1ll * (x / tmp) * to[now]; x %= tmp;
	}

	printf("%lld\n", ret);
}

int main()
{
	freopen("shopping.in", "r", stdin);
	freopen("shopping.out", "w", stdout);
	
	in(n); in(m);

	FOR(i, 1, n) {
		in(w[i]), in(p[i]);
		all[++all[0]] = w[i];
	}

	FOR(i, 1, m) {
		in(opt[i][0]);
		if (opt[i][0] == 1) in(opt[i][1]), in(opt[i][2]), in(opt[i][3]);
		else in(opt[i][1]);

		if (opt[i][0] == 1) all[++all[0]] = opt[i][2];
	}

	std::sort(all + 1, all + all[0] + 1);
	all[0] = std::unique(all + 1, all + all[0] + 1) - all - 1;

	FOR(i, 1, all[0]) to[i] = all[i];

	FOR(i, 1, n) w[i] = std::lower_bound(all + 1, all + all[0] + 1, w[i]) - all;
	FOR(i, 1, m) if (opt[i][0] == 1)
		opt[i][2] = std::lower_bound(all + 1, all + all[0] + 1, opt[i][2]) - all;

	FOR(i, 1, all[0]) value[i].insert(inf);
	FOR(i, 1, n) value[w[i]].insert(p[i]);

	build(1, 1, all[0]);

	FOR(i, 1, m) {
		if (opt[i][0] == 1) {
			int x = opt[i][1];
			value[w[x]].erase(value[w[x]].find(p[x]));

			minx[pos[w[x]]] = *value[w[x]].begin();
			
			L = w[x];
			modify(1, 1, all[0]);
			
			value[w[x] = opt[i][2]].insert(p[x] = opt[i][3]);

			minx[pos[w[x]]] = *value[w[x]].begin();
			
			L = w[x];
			modify(1, 1, all[0]);
		}
		else find(opt[i][1]);
	}
	
	return 0;
}
